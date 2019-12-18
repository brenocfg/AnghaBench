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
struct touchit213 {int /*<<< orphan*/  dev; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct touchit213*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct touchit213* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void touchit213_disconnect(struct serio *serio)
{
	struct touchit213 *touchit213 = serio_get_drvdata(serio);

	input_get_device(touchit213->dev);
	input_unregister_device(touchit213->dev);
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	input_put_device(touchit213->dev);
	kfree(touchit213);
}