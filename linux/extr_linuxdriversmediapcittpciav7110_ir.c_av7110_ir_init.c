#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct proc_dir_entry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int version; int /*<<< orphan*/  product; scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct TYPE_10__ {int /*<<< orphan*/  ir_handler; int /*<<< orphan*/  ir_tasklet; int /*<<< orphan*/  key_map; int /*<<< orphan*/  input_phys; struct input_dev* input_dev; int /*<<< orphan*/  keyup_timer; } ;
struct av7110 {TYPE_5__ ir; TYPE_3__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ vendor; int /*<<< orphan*/  subsystem_device; scalar_t__ subsystem_vendor; } ;
struct TYPE_8__ {TYPE_4__* pci; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct av7110**) ; 
 int /*<<< orphan*/  BUS_PCI ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  av7110_check_ir_config (struct av7110*,int) ; 
 int /*<<< orphan*/  av7110_emit_key ; 
 int /*<<< orphan*/  av7110_emit_keyup ; 
 int /*<<< orphan*/  av7110_ir_proc_fops ; 
 int av_cnt ; 
 struct av7110** av_list ; 
 int /*<<< orphan*/  default_key_map ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_enable_softrepeat (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_register_keys (TYPE_5__*) ; 
 int /*<<< orphan*/  ir_handler ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* pci_name (TYPE_4__*) ; 
 struct proc_dir_entry* proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_set_size (struct proc_dir_entry*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int av7110_ir_init(struct av7110 *av7110)
{
	struct input_dev *input_dev;
	static struct proc_dir_entry *e;
	int err;

	if (av_cnt >= ARRAY_SIZE(av_list))
		return -ENOSPC;

	av_list[av_cnt++] = av7110;
	av7110_check_ir_config(av7110, true);

	timer_setup(&av7110->ir.keyup_timer, av7110_emit_keyup, 0);

	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	av7110->ir.input_dev = input_dev;
	snprintf(av7110->ir.input_phys, sizeof(av7110->ir.input_phys),
		"pci-%s/ir0", pci_name(av7110->dev->pci));

	input_dev->name = "DVB on-card IR receiver";

	input_dev->phys = av7110->ir.input_phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->id.version = 2;
	if (av7110->dev->pci->subsystem_vendor) {
		input_dev->id.vendor = av7110->dev->pci->subsystem_vendor;
		input_dev->id.product = av7110->dev->pci->subsystem_device;
	} else {
		input_dev->id.vendor = av7110->dev->pci->vendor;
		input_dev->id.product = av7110->dev->pci->device;
	}
	input_dev->dev.parent = &av7110->dev->pci->dev;
	/* initial keymap */
	memcpy(av7110->ir.key_map, default_key_map, sizeof av7110->ir.key_map);
	input_register_keys(&av7110->ir);
	err = input_register_device(input_dev);
	if (err) {
		input_free_device(input_dev);
		return err;
	}

	/*
	 * Input core's default autorepeat is 33 cps with 250 msec
	 * delay, let's adjust to numbers more suitable for remote
	 * control.
	 */
	input_enable_softrepeat(input_dev, 250, 125);

	if (av_cnt == 1) {
		e = proc_create("av7110_ir", S_IWUSR, NULL, &av7110_ir_proc_fops);
		if (e)
			proc_set_size(e, 4 + 256 * sizeof(u16));
	}

	tasklet_init(&av7110->ir.ir_tasklet, av7110_emit_key, (unsigned long) &av7110->ir);
	av7110->ir.ir_handler = ir_handler;

	return 0;
}