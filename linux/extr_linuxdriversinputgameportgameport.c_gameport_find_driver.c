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
struct gameport {int /*<<< orphan*/  name; int /*<<< orphan*/  phys; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int device_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gameport_find_driver(struct gameport *gameport)
{
	int error;

	error = device_attach(&gameport->dev);
	if (error < 0)
		dev_warn(&gameport->dev,
			 "device_attach() failed for %s (%s), error: %d\n",
			 gameport->phys, gameport->name, error);
}