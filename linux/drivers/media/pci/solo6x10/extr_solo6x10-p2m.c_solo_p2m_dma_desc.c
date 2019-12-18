#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct solo_p2m_dev {int desc_count; int desc_idx; int /*<<< orphan*/  mutex; scalar_t__ error; int /*<<< orphan*/  completion; struct solo_p2m_desc* descs; } ;
struct solo_p2m_desc {unsigned int dma_addr; unsigned int ext_addr; unsigned int cfg; unsigned int ctrl; } ;
struct solo_dev {scalar_t__ type; int /*<<< orphan*/  p2m_timeouts; int /*<<< orphan*/  p2m_jiffies; struct solo_p2m_dev* p2m_dev; int /*<<< orphan*/  p2m_count; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EIO ; 
 scalar_t__ SOLO_DEV_6110 ; 
 unsigned int SOLO_NR_P2M ; 
 int /*<<< orphan*/  SOLO_P2M_CONFIG (unsigned int) ; 
 int /*<<< orphan*/  SOLO_P2M_CONTROL (unsigned int) ; 
 int /*<<< orphan*/  SOLO_P2M_DESC_ID (unsigned int) ; 
 unsigned int SOLO_P2M_DESC_MODE ; 
 int /*<<< orphan*/  SOLO_P2M_DES_ADR (unsigned int) ; 
 int /*<<< orphan*/  SOLO_P2M_EXT_ADR (unsigned int) ; 
 int /*<<< orphan*/  SOLO_P2M_EXT_CFG (unsigned int) ; 
 int /*<<< orphan*/  SOLO_P2M_TAR_ADR (unsigned int) ; 
 scalar_t__ WARN_ON_ONCE (scalar_t__) ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ desc_mode ; 
 scalar_t__ multi_p2m ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int solo_p2m_dma_desc(struct solo_dev *solo_dev,
		      struct solo_p2m_desc *desc, dma_addr_t desc_dma,
		      int desc_cnt)
{
	struct solo_p2m_dev *p2m_dev;
	unsigned int timeout;
	unsigned int config = 0;
	int ret = 0;
	unsigned int p2m_id = 0;

	/* Get next ID. According to Softlogic, 6110 has problems on !=0 P2M */
	if (solo_dev->type != SOLO_DEV_6110 && multi_p2m)
		p2m_id = atomic_inc_return(&solo_dev->p2m_count) % SOLO_NR_P2M;

	p2m_dev = &solo_dev->p2m_dev[p2m_id];

	if (mutex_lock_interruptible(&p2m_dev->mutex))
		return -EINTR;

	reinit_completion(&p2m_dev->completion);
	p2m_dev->error = 0;

	if (desc_cnt > 1 && solo_dev->type != SOLO_DEV_6110 && desc_mode) {
		/* For 6010 with more than one desc, we can do a one-shot */
		p2m_dev->desc_count = p2m_dev->desc_idx = 0;
		config = solo_reg_read(solo_dev, SOLO_P2M_CONFIG(p2m_id));

		solo_reg_write(solo_dev, SOLO_P2M_DES_ADR(p2m_id), desc_dma);
		solo_reg_write(solo_dev, SOLO_P2M_DESC_ID(p2m_id), desc_cnt);
		solo_reg_write(solo_dev, SOLO_P2M_CONFIG(p2m_id), config |
			       SOLO_P2M_DESC_MODE);
	} else {
		/* For single descriptors and 6110, we need to run each desc */
		p2m_dev->desc_count = desc_cnt;
		p2m_dev->desc_idx = 1;
		p2m_dev->descs = desc;

		solo_reg_write(solo_dev, SOLO_P2M_TAR_ADR(p2m_id),
			       desc[1].dma_addr);
		solo_reg_write(solo_dev, SOLO_P2M_EXT_ADR(p2m_id),
			       desc[1].ext_addr);
		solo_reg_write(solo_dev, SOLO_P2M_EXT_CFG(p2m_id),
			       desc[1].cfg);
		solo_reg_write(solo_dev, SOLO_P2M_CONTROL(p2m_id),
			       desc[1].ctrl);
	}

	timeout = wait_for_completion_timeout(&p2m_dev->completion,
					      solo_dev->p2m_jiffies);

	if (WARN_ON_ONCE(p2m_dev->error))
		ret = -EIO;
	else if (timeout == 0) {
		solo_dev->p2m_timeouts++;
		ret = -EAGAIN;
	}

	solo_reg_write(solo_dev, SOLO_P2M_CONTROL(p2m_id), 0);

	/* Don't write here for the no_desc_mode case, because config is 0.
	 * We can't test no_desc_mode again, it might race. */
	if (desc_cnt > 1 && solo_dev->type != SOLO_DEV_6110 && config)
		solo_reg_write(solo_dev, SOLO_P2M_CONFIG(p2m_id), config);

	mutex_unlock(&p2m_dev->mutex);

	return ret;
}