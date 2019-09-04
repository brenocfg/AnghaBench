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
struct atkbd {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_CMD_RESET_DEF ; 
 int /*<<< orphan*/  atkbd_disable (struct atkbd*) ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atkbd* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static void atkbd_cleanup(struct serio *serio)
{
	struct atkbd *atkbd = serio_get_drvdata(serio);

	atkbd_disable(atkbd);
	ps2_command(&atkbd->ps2dev, NULL, ATKBD_CMD_RESET_DEF);
}