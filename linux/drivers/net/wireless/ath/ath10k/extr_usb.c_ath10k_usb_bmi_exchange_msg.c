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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_USB_CONTROL_REQ_RECV_BMI_RESP ; 
 int /*<<< orphan*/  ATH10K_USB_CONTROL_REQ_SEND_BMI_CMD ; 
 int ath10k_usb_submit_ctrl_in (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int ath10k_usb_submit_ctrl_out (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_usb_bmi_exchange_msg(struct ath10k *ar,
				       void *req, u32 req_len,
				       void *resp, u32 *resp_len)
{
	int ret;

	if (req) {
		ret = ath10k_usb_submit_ctrl_out(ar,
						 ATH10K_USB_CONTROL_REQ_SEND_BMI_CMD,
						 0, 0, req, req_len);
		if (ret) {
			ath10k_warn(ar,
				    "unable to send the bmi data to the device: %d\n",
				    ret);
			return ret;
		}
	}

	if (resp) {
		ret = ath10k_usb_submit_ctrl_in(ar,
						ATH10K_USB_CONTROL_REQ_RECV_BMI_RESP,
						0, 0, resp, *resp_len);
		if (ret) {
			ath10k_warn(ar,
				    "Unable to read the bmi data from the device: %d\n",
				    ret);
			return ret;
		}
	}

	return 0;
}