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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_psb_private {int /*<<< orphan*/  lock_2d; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_RSGX32 (scalar_t__) ; 
 scalar_t__ PSB_SGX_2D_SLAVE_PORT ; 
 int /*<<< orphan*/  PSB_WSGX32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int psb_2d_wait_available (struct drm_psb_private*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int psbfb_2d_submit(struct drm_psb_private *dev_priv, uint32_t *cmdbuf,
								unsigned size)
{
	int ret = 0;
	int i;
	unsigned submit_size;
	unsigned long flags;

	spin_lock_irqsave(&dev_priv->lock_2d, flags);
	while (size > 0) {
		submit_size = (size < 0x60) ? size : 0x60;
		size -= submit_size;
		ret = psb_2d_wait_available(dev_priv, submit_size);
		if (ret)
			break;

		submit_size <<= 2;

		for (i = 0; i < submit_size; i += 4)
			PSB_WSGX32(*cmdbuf++, PSB_SGX_2D_SLAVE_PORT + i);

		(void)PSB_RSGX32(PSB_SGX_2D_SLAVE_PORT + i - 4);
	}
	spin_unlock_irqrestore(&dev_priv->lock_2d, flags);
	return ret;
}