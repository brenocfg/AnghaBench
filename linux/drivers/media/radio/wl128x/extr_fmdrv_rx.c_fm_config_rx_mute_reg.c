#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int mute_mode; scalar_t__ rf_depend_mute; } ;
struct fmdev {TYPE_1__ rx; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
#define  FM_MUTE_ATTENUATE 130 
#define  FM_MUTE_OFF 129 
#define  FM_MUTE_ON 128 
 int /*<<< orphan*/  FM_RX_AC_MUTE_MODE ; 
 scalar_t__ FM_RX_RF_DEPENDENT_MUTE_ON ; 
 int /*<<< orphan*/  FM_RX_RF_DEP_MODE ; 
 int /*<<< orphan*/  FM_RX_SOFT_MUTE_FORCE_MODE ; 
 int /*<<< orphan*/  FM_RX_UNMUTE_MODE ; 
 int /*<<< orphan*/  MUTE_STATUS_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fm_config_rx_mute_reg(struct fmdev *fmdev)
{
	u16 payload, muteval;
	int ret;

	muteval = 0;
	switch (fmdev->rx.mute_mode) {
	case FM_MUTE_ON:
		muteval = FM_RX_AC_MUTE_MODE;
		break;

	case FM_MUTE_OFF:
		muteval = FM_RX_UNMUTE_MODE;
		break;

	case FM_MUTE_ATTENUATE:
		muteval = FM_RX_SOFT_MUTE_FORCE_MODE;
		break;
	}
	if (fmdev->rx.rf_depend_mute == FM_RX_RF_DEPENDENT_MUTE_ON)
		muteval |= FM_RX_RF_DEP_MODE;
	else
		muteval &= ~FM_RX_RF_DEP_MODE;

	payload = muteval;
	ret = fmc_send_cmd(fmdev, MUTE_STATUS_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}