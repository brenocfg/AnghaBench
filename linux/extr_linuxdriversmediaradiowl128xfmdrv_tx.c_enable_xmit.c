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
typedef  void* u8 ;
typedef  void* u16 ;
struct fmtx_data {void* xmit_state; } ;
struct fmdev {int /*<<< orphan*/  flag; int /*<<< orphan*/  maintask_comp; struct fmtx_data tx_data; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FM_CORE_TX_XMITING ; 
 int /*<<< orphan*/  FM_DRV_TX_TIMEOUT ; 
 void* FM_POW_ENB_EVENT ; 
 int /*<<< orphan*/  INT_MASK_SET ; 
 int /*<<< orphan*/  POWER_ENB_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enable_xmit(struct fmdev *fmdev, u8 new_xmit_state)
{
	struct fmtx_data *tx = &fmdev->tx_data;
	unsigned long timeleft;
	u16 payload;
	int ret;

	/* Enable POWER_ENB interrupts */
	payload = FM_POW_ENB_EVENT;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	/* Set Power Enable */
	payload = new_xmit_state;
	ret = fmc_send_cmd(fmdev, POWER_ENB_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	/* Wait for Power Enabled */
	init_completion(&fmdev->maintask_comp);
	timeleft = wait_for_completion_timeout(&fmdev->maintask_comp,
			FM_DRV_TX_TIMEOUT);
	if (!timeleft) {
		fmerr("Timeout(%d sec),didn't get tune ended interrupt\n",
			   jiffies_to_msecs(FM_DRV_TX_TIMEOUT) / 1000);
		return -ETIMEDOUT;
	}

	set_bit(FM_CORE_TX_XMITING, &fmdev->flag);
	tx->xmit_state = new_xmit_state;

	return 0;
}