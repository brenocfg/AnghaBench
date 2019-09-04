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
struct axp288_extcon_info {int /*<<< orphan*/  role_sw; int /*<<< orphan*/  role_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axp288_put_role_sw(void *data)
{
	struct axp288_extcon_info *info = data;

	cancel_work_sync(&info->role_work);
	usb_role_switch_put(info->role_sw);
}