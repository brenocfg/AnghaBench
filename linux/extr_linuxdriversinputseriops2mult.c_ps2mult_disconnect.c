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
struct ps2mult {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2MULT_SESSION_END ; 
 int /*<<< orphan*/  kfree (struct ps2mult*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct ps2mult* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_write (struct serio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2mult_disconnect(struct serio *serio)
{
	struct ps2mult *psm = serio_get_drvdata(serio);

	/* Note that serio core already take care of children ports */
	serio_write(serio, PS2MULT_SESSION_END);
	serio_close(serio);
	kfree(psm);

	serio_set_drvdata(serio, NULL);
}