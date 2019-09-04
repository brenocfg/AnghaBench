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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fmtx_data {int /*<<< orphan*/  preemph; } ;
struct fmdev {scalar_t__ curr_fmmode; struct fmtx_data tx_data; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ FM_MODE_TX ; 
 int /*<<< orphan*/  FM_TX_PREEMPH_50US ; 
 int /*<<< orphan*/  FM_TX_PREEMPH_75US ; 
 int /*<<< orphan*/  FM_TX_PREEMPH_OFF ; 
 int /*<<< orphan*/  PREMPH_SET ; 
 int /*<<< orphan*/  REG_WR ; 
#define  V4L2_PREEMPHASIS_50_uS 130 
#define  V4L2_PREEMPHASIS_75_uS 129 
#define  V4L2_PREEMPHASIS_DISABLED 128 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int fm_tx_set_preemph_filter(struct fmdev *fmdev, u32 preemphasis)
{
	struct fmtx_data *tx = &fmdev->tx_data;
	u16 payload;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_TX)
		return -EPERM;

	switch (preemphasis) {
	case V4L2_PREEMPHASIS_DISABLED:
		payload = FM_TX_PREEMPH_OFF;
		break;
	case V4L2_PREEMPHASIS_50_uS:
		payload = FM_TX_PREEMPH_50US;
		break;
	case V4L2_PREEMPHASIS_75_uS:
		payload = FM_TX_PREEMPH_75US;
		break;
	}

	ret = fmc_send_cmd(fmdev, PREMPH_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	tx->preemph = payload;

	return ret;
}