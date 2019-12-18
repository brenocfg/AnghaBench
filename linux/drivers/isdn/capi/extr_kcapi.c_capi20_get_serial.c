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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct capi_ctr {scalar_t__ state; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 scalar_t__ CAPI_CTR_RUNNING ; 
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 int /*<<< orphan*/  CAPI_SERIAL_LEN ; 
 int /*<<< orphan*/  capi_controller_lock ; 
 int /*<<< orphan*/  driver_serial ; 
 struct capi_ctr* get_capi_ctr_by_nr (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 capi20_get_serial(u32 contr, u8 *serial)
{
	struct capi_ctr *ctr;
	u16 ret;

	if (contr == 0) {
		strlcpy(serial, driver_serial, CAPI_SERIAL_LEN);
		return CAPI_NOERROR;
	}

	mutex_lock(&capi_controller_lock);

	ctr = get_capi_ctr_by_nr(contr);
	if (ctr && ctr->state == CAPI_CTR_RUNNING) {
		strlcpy(serial, ctr->serial, CAPI_SERIAL_LEN);
		ret = CAPI_NOERROR;
	} else
		ret = CAPI_REGNOTINSTALLED;

	mutex_unlock(&capi_controller_lock);
	return ret;
}