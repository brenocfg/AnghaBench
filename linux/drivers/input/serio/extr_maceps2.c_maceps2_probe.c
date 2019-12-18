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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maceps2_allocate_port (int) ; 
 int /*<<< orphan*/ * maceps2_port ; 
 int /*<<< orphan*/  serio_register_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maceps2_probe(struct platform_device *dev)
{
	maceps2_port[0] = maceps2_allocate_port(0);
	maceps2_port[1] = maceps2_allocate_port(1);
	if (!maceps2_port[0] || !maceps2_port[1]) {
		kfree(maceps2_port[0]);
		kfree(maceps2_port[1]);
		return -ENOMEM;
	}

	serio_register_port(maceps2_port[0]);
	serio_register_port(maceps2_port[1]);

	return 0;
}