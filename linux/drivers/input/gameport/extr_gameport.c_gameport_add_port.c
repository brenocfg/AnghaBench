#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gameport {int /*<<< orphan*/  name; int /*<<< orphan*/  phys; int /*<<< orphan*/  dev; int /*<<< orphan*/  speed; scalar_t__ io; int /*<<< orphan*/  node; TYPE_1__* parent; } ;
struct TYPE_2__ {struct gameport* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gameport_list ; 
 int /*<<< orphan*/  gameport_measure_speed (struct gameport*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_gameport_measure_speed (struct gameport*) ; 
 scalar_t__ use_ktime ; 

__attribute__((used)) static void gameport_add_port(struct gameport *gameport)
{
	int error;

	if (gameport->parent)
		gameport->parent->child = gameport;

	gameport->speed = use_ktime ?
		gameport_measure_speed(gameport) :
		old_gameport_measure_speed(gameport);

	list_add_tail(&gameport->node, &gameport_list);

	if (gameport->io)
		dev_info(&gameport->dev, "%s is %s, io %#x, speed %dkHz\n",
			 gameport->name, gameport->phys, gameport->io, gameport->speed);
	else
		dev_info(&gameport->dev, "%s is %s, speed %dkHz\n",
			gameport->name, gameport->phys, gameport->speed);

	error = device_add(&gameport->dev);
	if (error)
		dev_err(&gameport->dev,
			"device_add() failed for %s (%s), error: %d\n",
			gameport->phys, gameport->name, error);
}