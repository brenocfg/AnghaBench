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
struct gameport_driver {int dummy; } ;
struct gameport {int dummy; } ;
struct analog_port {TYPE_1__* analog; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ mask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int analog_init_device (struct analog_port*,TYPE_1__*,int) ; 
 int analog_init_masks (struct analog_port*) ; 
 int analog_init_port (struct gameport*,struct gameport_driver*,struct analog_port*) ; 
 int /*<<< orphan*/  analog_poll ; 
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gameport_set_poll_handler (struct gameport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_set_poll_interval (struct gameport*,int) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct analog_port*) ; 
 struct analog_port* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int analog_connect(struct gameport *gameport, struct gameport_driver *drv)
{
	struct analog_port *port;
	int i;
	int err;

	if (!(port = kzalloc(sizeof(struct analog_port), GFP_KERNEL)))
		return - ENOMEM;

	err = analog_init_port(gameport, drv, port);
	if (err)
		goto fail1;

	err = analog_init_masks(port);
	if (err)
		goto fail2;

	gameport_set_poll_handler(gameport, analog_poll);
	gameport_set_poll_interval(gameport, 10);

	for (i = 0; i < 2; i++)
		if (port->analog[i].mask) {
			err = analog_init_device(port, port->analog + i, i);
			if (err)
				goto fail3;
		}

	return 0;

 fail3: while (--i >= 0)
		if (port->analog[i].mask)
			input_unregister_device(port->analog[i].dev);
 fail2:	gameport_close(gameport);
 fail1:	gameport_set_drvdata(gameport, NULL);
	kfree(port);
	return err;
}