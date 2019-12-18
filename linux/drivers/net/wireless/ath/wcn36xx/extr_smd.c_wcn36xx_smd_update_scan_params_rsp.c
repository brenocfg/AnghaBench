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
struct wcn36xx_hal_update_scan_params_resp {int status; } ;

/* Variables and functions */
 int WCN36XX_FW_MSG_PNO_VERSION_MASK ; 
 int WCN36XX_FW_MSG_RESULT_SUCCESS ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

__attribute__((used)) static int wcn36xx_smd_update_scan_params_rsp(void *buf, size_t len)
{
	struct wcn36xx_hal_update_scan_params_resp *rsp;

	rsp = (struct wcn36xx_hal_update_scan_params_resp *)buf;

	/* Remove the PNO version bit */
	rsp->status &= (~(WCN36XX_FW_MSG_PNO_VERSION_MASK));

	if (WCN36XX_FW_MSG_RESULT_SUCCESS != rsp->status) {
		wcn36xx_warn("error response from update scan\n");
		return rsp->status;
	}

	return 0;
}