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
struct serio {struct rpckbd_data* port_data; } ;
struct rpckbd_data {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpckbd_data*) ; 
 struct serio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (struct serio*) ; 

__attribute__((used)) static int rpckbd_remove(struct platform_device *dev)
{
	struct serio *serio = platform_get_drvdata(dev);
	struct rpckbd_data *rpckbd = serio->port_data;

	serio_unregister_port(serio);
	kfree(rpckbd);

	return 0;
}