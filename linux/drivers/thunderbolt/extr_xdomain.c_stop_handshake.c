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
struct tb_xdomain {int /*<<< orphan*/  properties_changed_work; int /*<<< orphan*/  get_properties_work; int /*<<< orphan*/  get_uuid_work; scalar_t__ properties_changed_retries; scalar_t__ properties_retries; scalar_t__ uuid_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_handshake(struct tb_xdomain *xd)
{
	xd->uuid_retries = 0;
	xd->properties_retries = 0;
	xd->properties_changed_retries = 0;

	cancel_delayed_work_sync(&xd->get_uuid_work);
	cancel_delayed_work_sync(&xd->get_properties_work);
	cancel_delayed_work_sync(&xd->properties_changed_work);
}