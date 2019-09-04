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
typedef  int u8 ;
struct pti_masterchannel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ia_modem; int /*<<< orphan*/  ia_os; int /*<<< orphan*/  ia_app; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_BASE_ID ; 
 int /*<<< orphan*/  MAX_APP_IDS ; 
 int /*<<< orphan*/  MAX_MODEM_IDS ; 
 int /*<<< orphan*/  MAX_OS_IDS ; 
 int /*<<< orphan*/  MODEM_BASE_ID ; 
 int /*<<< orphan*/  OS_BASE_ID ; 
 int /*<<< orphan*/  alloclock ; 
 TYPE_1__* drv_data ; 
 struct pti_masterchannel* get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct pti_masterchannel *pti_request_masterchannel(u8 type,
						    const char *thread_name)
{
	struct pti_masterchannel *mc;

	mutex_lock(&alloclock);

	switch (type) {

	case 0:
		mc = get_id(drv_data->ia_app, MAX_APP_IDS,
			    APP_BASE_ID, thread_name);
		break;

	case 1:
		mc = get_id(drv_data->ia_os, MAX_OS_IDS,
			    OS_BASE_ID, thread_name);
		break;

	case 2:
		mc = get_id(drv_data->ia_modem, MAX_MODEM_IDS,
			    MODEM_BASE_ID, thread_name);
		break;
	default:
		mc = NULL;
	}

	mutex_unlock(&alloclock);
	return mc;
}