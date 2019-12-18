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
struct ps2dev {TYPE_1__* serio; } ;
struct atkbd {struct ps2dev ps2dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_CMD_RESET_DIS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atkbd_deactivate(struct atkbd *atkbd)
{
	struct ps2dev *ps2dev = &atkbd->ps2dev;

	if (ps2_command(ps2dev, NULL, ATKBD_CMD_RESET_DIS))
		dev_err(&ps2dev->serio->dev,
			"Failed to deactivate keyboard on %s\n",
			ps2dev->serio->phys);
}