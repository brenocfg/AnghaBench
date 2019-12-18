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
struct cdns3 {int role; int /*<<< orphan*/  mutex; TYPE_1__** roles; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  (* stop ) (struct cdns3*) ;} ;

/* Variables and functions */
 scalar_t__ CDNS3_ROLE_STATE_INACTIVE ; 
 int USB_ROLE_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cdns3*) ; 

__attribute__((used)) static void cdns3_role_stop(struct cdns3 *cdns)
{
	enum usb_role role = cdns->role;

	if (WARN_ON(role > USB_ROLE_DEVICE))
		return;

	if (cdns->roles[role]->state == CDNS3_ROLE_STATE_INACTIVE)
		return;

	mutex_lock(&cdns->mutex);
	cdns->roles[role]->stop(cdns);
	cdns->roles[role]->state = CDNS3_ROLE_STATE_INACTIVE;
	mutex_unlock(&cdns->mutex);
}