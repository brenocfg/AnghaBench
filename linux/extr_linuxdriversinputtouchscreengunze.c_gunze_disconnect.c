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
struct serio {int dummy; } ;
struct gunze {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gunze*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct gunze* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gunze_disconnect(struct serio *serio)
{
	struct gunze *gunze = serio_get_drvdata(serio);

	input_get_device(gunze->dev);
	input_unregister_device(gunze->dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	input_put_device(gunze->dev);
	kfree(gunze);
}