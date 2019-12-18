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
struct serio_driver {int dummy; } ;
struct serio {TYPE_1__* ports; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; TYPE_1__* out_port; TYPE_1__* in_port; struct serio* mx_serio; int /*<<< orphan*/  lock; int /*<<< orphan*/  write; } ;
struct ps2mult {TYPE_1__* ports; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; TYPE_1__* out_port; TYPE_1__* in_port; struct ps2mult* mx_serio; int /*<<< orphan*/  lock; int /*<<< orphan*/  write; } ;
struct TYPE_2__ {struct serio* serio; int /*<<< orphan*/  sel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PS2MULT_KBD_PORT ; 
 int PS2MULT_NUM_PORTS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct serio*) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ps2mult_controls ; 
 int ps2mult_create_port (struct serio*,int) ; 
 int /*<<< orphan*/  ps2mult_reset (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct serio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ps2mult_connect(struct serio *serio, struct serio_driver *drv)
{
	struct ps2mult *psm;
	int i;
	int error;

	if (!serio->write)
		return -EINVAL;

	psm = kzalloc(sizeof(*psm), GFP_KERNEL);
	if (!psm)
		return -ENOMEM;

	spin_lock_init(&psm->lock);
	psm->mx_serio = serio;

	for (i = 0; i < PS2MULT_NUM_PORTS; i++) {
		psm->ports[i].sel = ps2mult_controls[i];
		error = ps2mult_create_port(psm, i);
		if (error)
			goto err_out;
	}

	psm->in_port = psm->out_port = &psm->ports[PS2MULT_KBD_PORT];

	serio_set_drvdata(serio, psm);
	error = serio_open(serio, drv);
	if (error)
		goto err_out;

	ps2mult_reset(psm);

	for (i = 0; i <  PS2MULT_NUM_PORTS; i++) {
		struct serio *s = psm->ports[i].serio;

		dev_info(&serio->dev, "%s port at %s\n", s->name, serio->phys);
		serio_register_port(s);
	}

	return 0;

err_out:
	while (--i >= 0)
		kfree(psm->ports[i].serio);
	kfree(psm);
	return error;
}