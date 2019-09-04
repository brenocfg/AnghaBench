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
struct cobra {int exists; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 struct cobra* gameport_get_drvdata (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cobra*) ; 

__attribute__((used)) static void cobra_disconnect(struct gameport *gameport)
{
	struct cobra *cobra = gameport_get_drvdata(gameport);
	int i;

	for (i = 0; i < 2; i++)
		if ((cobra->exists >> i) & 1)
			input_unregister_device(cobra->dev[i]);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(cobra);
}