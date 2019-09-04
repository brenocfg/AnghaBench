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
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CAPI_CTR_RUNNING ; 
 int CAPI_MAXCONTR ; 
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 TYPE_1__** capi_controller ; 
 int /*<<< orphan*/  capi_controller_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u16 capi20_isinstalled(void)
{
	u16 ret = CAPI_REGNOTINSTALLED;
	int i;

	mutex_lock(&capi_controller_lock);

	for (i = 0; i < CAPI_MAXCONTR; i++)
		if (capi_controller[i] &&
		    capi_controller[i]->state == CAPI_CTR_RUNNING) {
			ret = CAPI_NOERROR;
			break;
		}

	mutex_unlock(&capi_controller_lock);

	return ret;
}