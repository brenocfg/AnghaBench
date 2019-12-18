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
struct con_driver {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_DRIVER_FLAG_ATTR ; 

__attribute__((used)) static void vtconsole_deinit_device(struct con_driver *con)
{
	con->flag &= ~CON_DRIVER_FLAG_ATTR;
}