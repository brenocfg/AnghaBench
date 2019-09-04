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
struct gameport_driver {int dummy; } ;
struct gameport {int /*<<< orphan*/  drv_mutex; struct gameport_driver* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gameport_set_drv(struct gameport *gameport, struct gameport_driver *drv)
{
	mutex_lock(&gameport->drv_mutex);
	gameport->drv = drv;
	mutex_unlock(&gameport->drv_mutex);
}