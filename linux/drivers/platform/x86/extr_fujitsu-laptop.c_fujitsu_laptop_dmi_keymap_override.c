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
struct dmi_system_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  keymap ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fujitsu_laptop_dmi_keymap_override(const struct dmi_system_id *id)
{
	pr_info("Identified laptop model '%s'\n", id->ident);
	keymap = id->driver_data;
	return 1;
}