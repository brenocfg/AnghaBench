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
struct gameport {int dummy; } ;
struct adi_port {TYPE_1__* adi; } ;
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 struct adi_port* gameport_get_drvdata (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adi_port*) ; 

__attribute__((used)) static void adi_disconnect(struct gameport *gameport)
{
	int i;
	struct adi_port *port = gameport_get_drvdata(gameport);

	for (i = 0; i < 2; i++)
		if (port->adi[i].length > 0)
			input_unregister_device(port->adi[i].dev);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(port);
}