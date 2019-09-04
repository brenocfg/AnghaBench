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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct serio {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct TYPE_6__ {TYPE_2__* port; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* parkbd_dev ; 
 int /*<<< orphan*/  parkbd_mode ; 
 int /*<<< orphan*/  parkbd_write ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct serio *parkbd_allocate_serio(void)
{
	struct serio *serio;

	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (serio) {
		serio->id.type = parkbd_mode;
		serio->write = parkbd_write,
		strlcpy(serio->name, "PARKBD AT/XT keyboard adapter", sizeof(serio->name));
		snprintf(serio->phys, sizeof(serio->phys), "%s/serio0", parkbd_dev->port->name);
	}

	return serio;
}