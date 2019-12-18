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
struct grip_mp {TYPE_1__** port; struct gameport* gameport; } ;
struct gameport_driver {int dummy; } ;
struct gameport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMEPORT_MODE_RAW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 int gameport_open (struct gameport*,struct gameport_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,struct grip_mp*) ; 
 int /*<<< orphan*/  gameport_set_poll_handler (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_poll_interval (struct gameport*,int) ; 
 int /*<<< orphan*/  grip_poll ; 
 int /*<<< orphan*/  kfree (struct grip_mp*) ; 
 struct grip_mp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiport_init (struct grip_mp*) ; 

__attribute__((used)) static int grip_connect(struct gameport *gameport, struct gameport_driver *drv)
{
	struct grip_mp *grip;
	int err;

	if (!(grip = kzalloc(sizeof(struct grip_mp), GFP_KERNEL)))
		return -ENOMEM;

	grip->gameport = gameport;

	gameport_set_drvdata(gameport, grip);

	err = gameport_open(gameport, drv, GAMEPORT_MODE_RAW);
	if (err)
		goto fail1;

	gameport_set_poll_handler(gameport, grip_poll);
	gameport_set_poll_interval(gameport, 20);

	if (!multiport_init(grip)) {
		err = -ENODEV;
		goto fail2;
	}

	if (!grip->port[0]->mode && !grip->port[1]->mode && !grip->port[2]->mode && !grip->port[3]->mode) {
		/* nothing plugged in */
		err = -ENODEV;
		goto fail2;
	}

	return 0;

fail2:	gameport_close(gameport);
fail1:	gameport_set_drvdata(gameport, NULL);
	kfree(grip);
	return err;
}