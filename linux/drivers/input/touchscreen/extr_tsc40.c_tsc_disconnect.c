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
struct tsc_ser {int /*<<< orphan*/  dev; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tsc_ser*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct tsc_ser* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tsc_disconnect(struct serio *serio)
{
	struct tsc_ser *ptsc = serio_get_drvdata(serio);

	serio_close(serio);

	input_unregister_device(ptsc->dev);
	kfree(ptsc);

	serio_set_drvdata(serio, NULL);
}