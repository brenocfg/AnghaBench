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
struct cxacru_data {int /*<<< orphan*/  usbatm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_REQUEST_CARD_GET_STATUS ; 
 int cxacru_cm (struct cxacru_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cxacru_card_status(struct cxacru_data *instance)
{
	int ret = cxacru_cm(instance, CM_REQUEST_CARD_GET_STATUS, NULL, 0, NULL, 0);

	if (ret < 0) {		/* firmware not loaded */
		usb_dbg(instance->usbatm, "cxacru_adsl_start: CARD_GET_STATUS returned %d\n", ret);
		return ret;
	}
	return 0;
}