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
struct serio_driver {int (* connect ) (struct serio*,struct serio_driver*) ;} ;
struct serio {int /*<<< orphan*/  drv_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct serio*,struct serio_driver*) ; 

__attribute__((used)) static int serio_connect_driver(struct serio *serio, struct serio_driver *drv)
{
	int retval;

	mutex_lock(&serio->drv_mutex);
	retval = drv->connect(serio, drv);
	mutex_unlock(&serio->drv_mutex);

	return retval;
}