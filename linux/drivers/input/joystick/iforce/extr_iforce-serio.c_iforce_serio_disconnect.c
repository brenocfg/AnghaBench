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
struct serio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct iforce_serio {TYPE_1__ iforce; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iforce_serio*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct iforce_serio* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_serio_disconnect(struct serio *serio)
{
	struct iforce_serio *iforce_serio = serio_get_drvdata(serio);

	input_unregister_device(iforce_serio->iforce.dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	kfree(iforce_serio);
}