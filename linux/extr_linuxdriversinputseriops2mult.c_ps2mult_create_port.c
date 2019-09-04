#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct serio {char* phys; TYPE_2__* port_data; struct serio* parent; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  write; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct ps2mult {TYPE_2__* ports; struct serio* mx_serio; } ;
struct TYPE_4__ {struct serio* serio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2mult_serio_start ; 
 int /*<<< orphan*/  ps2mult_serio_stop ; 
 int /*<<< orphan*/  ps2mult_serio_write ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ps2mult_create_port(struct ps2mult *psm, int i)
{
	struct serio *mx_serio = psm->mx_serio;
	struct serio *serio;

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!serio)
		return -ENOMEM;

	strlcpy(serio->name, "TQC PS/2 Multiplexer", sizeof(serio->name));
	snprintf(serio->phys, sizeof(serio->phys),
		 "%s/port%d", mx_serio->phys, i);
	serio->id.type = SERIO_8042;
	serio->write = ps2mult_serio_write;
	serio->start = ps2mult_serio_start;
	serio->stop = ps2mult_serio_stop;
	serio->parent = psm->mx_serio;
	serio->port_data = &psm->ports[i];

	psm->ports[i].serio = serio;

	return 0;
}