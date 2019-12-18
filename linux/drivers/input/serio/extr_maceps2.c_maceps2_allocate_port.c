#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct serio {TYPE_2__ dev; int /*<<< orphan*/ * port_data; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maceps2_close ; 
 TYPE_3__* maceps2_device ; 
 int /*<<< orphan*/  maceps2_open ; 
 int /*<<< orphan*/  maceps2_write ; 
 int /*<<< orphan*/ * port_data ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static struct serio *maceps2_allocate_port(int idx)
{
	struct serio *serio;

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (serio) {
		serio->id.type		= SERIO_8042;
		serio->write		= maceps2_write;
		serio->open		= maceps2_open;
		serio->close		= maceps2_close;
		snprintf(serio->name, sizeof(serio->name), "MACE PS/2 port%d", idx);
		snprintf(serio->phys, sizeof(serio->phys), "mace/serio%d", idx);
		serio->port_data	= &port_data[idx];
		serio->dev.parent	= &maceps2_device->dev;
	}

	return serio;
}