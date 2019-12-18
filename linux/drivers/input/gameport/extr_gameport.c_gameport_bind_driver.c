#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gameport_driver {int /*<<< orphan*/  (* disconnect ) (struct gameport*) ;int /*<<< orphan*/  description; scalar_t__ (* connect ) (struct gameport*,struct gameport_driver*) ;int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {int /*<<< orphan*/ * driver; } ;
struct gameport {TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int device_bind_driver (TYPE_1__*) ; 
 scalar_t__ stub1 (struct gameport*,struct gameport_driver*) ; 
 int /*<<< orphan*/  stub2 (struct gameport*) ; 

__attribute__((used)) static int gameport_bind_driver(struct gameport *gameport, struct gameport_driver *drv)
{
	int error;

	gameport->dev.driver = &drv->driver;
	if (drv->connect(gameport, drv)) {
		gameport->dev.driver = NULL;
		return -ENODEV;
	}

	error = device_bind_driver(&gameport->dev);
	if (error) {
		dev_warn(&gameport->dev,
			 "device_bind_driver() failed for %s (%s) and %s, error: %d\n",
			gameport->phys, gameport->name,
			drv->description, error);
		drv->disconnect(gameport);
		gameport->dev.driver = NULL;
		return error;
	}

	return 0;
}