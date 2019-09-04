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
struct grip {scalar_t__* dev; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 struct grip* gameport_get_drvdata (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct grip*) ; 

__attribute__((used)) static void grip_disconnect(struct gameport *gameport)
{
	struct grip *grip = gameport_get_drvdata(gameport);
	int i;

	for (i = 0; i < 2; i++)
		if (grip->dev[i])
			input_unregister_device(grip->dev[i]);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(grip);
}