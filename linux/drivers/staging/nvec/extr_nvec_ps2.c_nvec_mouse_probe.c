#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct serio {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct nvec_chip {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_7__ {TYPE_4__ notifier; struct nvec_chip* nvec; struct serio* ser_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 struct nvec_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvec_ps2_notifier ; 
 int /*<<< orphan*/  nvec_register_notifier (struct nvec_chip*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ ps2_dev ; 
 int /*<<< orphan*/  ps2_sendcommand ; 
 int /*<<< orphan*/  ps2_startstreaming ; 
 int /*<<< orphan*/  ps2_stopstreaming ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int nvec_mouse_probe(struct platform_device *pdev)
{
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	struct serio *ser_dev;

	ser_dev = kzalloc(sizeof(*ser_dev), GFP_KERNEL);
	if (!ser_dev)
		return -ENOMEM;

	ser_dev->id.type = SERIO_8042;
	ser_dev->write = ps2_sendcommand;
	ser_dev->start = ps2_startstreaming;
	ser_dev->stop = ps2_stopstreaming;

	strlcpy(ser_dev->name, "nvec mouse", sizeof(ser_dev->name));
	strlcpy(ser_dev->phys, "nvec", sizeof(ser_dev->phys));

	ps2_dev.ser_dev = ser_dev;
	ps2_dev.notifier.notifier_call = nvec_ps2_notifier;
	ps2_dev.nvec = nvec;
	nvec_register_notifier(nvec, &ps2_dev.notifier, 0);

	serio_register_port(ser_dev);

	return 0;
}