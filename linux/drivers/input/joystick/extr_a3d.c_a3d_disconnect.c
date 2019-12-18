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
struct gameport {int dummy; } ;
struct a3d {scalar_t__ adc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 struct a3d* gameport_get_drvdata (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gameport_unregister_port (scalar_t__) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct a3d*) ; 

__attribute__((used)) static void a3d_disconnect(struct gameport *gameport)
{
	struct a3d *a3d = gameport_get_drvdata(gameport);

	input_unregister_device(a3d->dev);
	if (a3d->adc)
		gameport_unregister_port(a3d->adc);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(a3d);
}