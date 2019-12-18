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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ath6kl {int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT ; 
 int /*<<< orphan*/  ATH6KL_USB_PIPE_RX_DATA ; 
 int /*<<< orphan*/  ATH6KL_USB_PIPE_TX_CTRL ; 
 int /*<<< orphan*/  ATH6KL_USB_PIPE_TX_DATA_LP ; 
 int /*<<< orphan*/  ATH6KL_USB_PIPE_TX_DATA_MP ; 
 int EPERM ; 
#define  HTC_CTRL_RSVD_SVC 133 
#define  WMI_CONTROL_SVC 132 
#define  WMI_DATA_BE_SVC 131 
#define  WMI_DATA_BK_SVC 130 
#define  WMI_DATA_VI_SVC 129 
#define  WMI_DATA_VO_SVC 128 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_usb_map_service_pipe(struct ath6kl *ar, u16 svc_id,
				       u8 *ul_pipe, u8 *dl_pipe)
{
	int status = 0;

	switch (svc_id) {
	case HTC_CTRL_RSVD_SVC:
	case WMI_CONTROL_SVC:
		*ul_pipe = ATH6KL_USB_PIPE_TX_CTRL;
		/* due to large control packets, shift to data pipe */
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		break;
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* if FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		break;
	case WMI_DATA_VI_SVC:

		if (test_bit(ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,
			     ar->fw_capabilities))
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		else
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_MP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* if FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		break;
	case WMI_DATA_VO_SVC:

		if (test_bit(ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,
			     ar->fw_capabilities))
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_LP;
		else
			*ul_pipe = ATH6KL_USB_PIPE_TX_DATA_MP;
		/*
		* Disable rxdata2 directly, it will be enabled
		* if FW enable rxdata2
		*/
		*dl_pipe = ATH6KL_USB_PIPE_RX_DATA;
		break;
	default:
		status = -EPERM;
		break;
	}

	return status;
}