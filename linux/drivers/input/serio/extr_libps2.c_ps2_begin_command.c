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
struct mutex {int dummy; } ;
struct ps2dev {struct mutex cmd_mutex; TYPE_1__* serio; } ;
struct TYPE_2__ {scalar_t__ ps2_cmd_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 

void ps2_begin_command(struct ps2dev *ps2dev)
{
	struct mutex *m = ps2dev->serio->ps2_cmd_mutex ?: &ps2dev->cmd_mutex;

	mutex_lock(m);
}