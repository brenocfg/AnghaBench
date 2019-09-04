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
struct parport {scalar_t__ number; } ;
struct pardevice {int dummy; } ;
struct pardev_cb {int /*<<< orphan*/  flags; } ;
struct gc {scalar_t__ parportno; TYPE_1__* pads; int /*<<< orphan*/  timer; struct pardevice* pd; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  gc_parport_cb ;
struct TYPE_4__ {int nargs; scalar_t__* args; } ;
struct TYPE_3__ {scalar_t__ dev; } ;

/* Variables and functions */
 int GC_MAX_DEVICES ; 
 int GC_MAX_PORTS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PARPORT_FLAG_EXCL ; 
 struct gc** gc_base ; 
 TYPE_2__* gc_cfg ; 
 scalar_t__ gc_setup_pad (struct gc*,int,int) ; 
 int /*<<< orphan*/  gc_timer ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gc*) ; 
 struct gc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct pardevice* parport_register_dev_model (struct parport*,char*,struct pardev_cb*,int) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_attach(struct parport *pp)
{
	struct gc *gc;
	struct pardevice *pd;
	int i, port_idx;
	int count = 0;
	int *pads, n_pads;
	struct pardev_cb gc_parport_cb;

	for (port_idx = 0; port_idx < GC_MAX_PORTS; port_idx++) {
		if (gc_cfg[port_idx].nargs == 0 || gc_cfg[port_idx].args[0] < 0)
			continue;

		if (gc_cfg[port_idx].args[0] == pp->number)
			break;
	}

	if (port_idx == GC_MAX_PORTS) {
		pr_debug("Not using parport%d.\n", pp->number);
		return;
	}
	pads = gc_cfg[port_idx].args + 1;
	n_pads = gc_cfg[port_idx].nargs - 1;

	memset(&gc_parport_cb, 0, sizeof(gc_parport_cb));
	gc_parport_cb.flags = PARPORT_FLAG_EXCL;

	pd = parport_register_dev_model(pp, "gamecon", &gc_parport_cb,
					port_idx);
	if (!pd) {
		pr_err("parport busy already - lp.o loaded?\n");
		return;
	}

	gc = kzalloc(sizeof(struct gc), GFP_KERNEL);
	if (!gc) {
		pr_err("Not enough memory\n");
		goto err_unreg_pardev;
	}

	mutex_init(&gc->mutex);
	gc->pd = pd;
	gc->parportno = pp->number;
	timer_setup(&gc->timer, gc_timer, 0);

	for (i = 0; i < n_pads && i < GC_MAX_DEVICES; i++) {
		if (!pads[i])
			continue;

		if (gc_setup_pad(gc, i, pads[i]))
			goto err_unreg_devs;

		count++;
	}

	if (count == 0) {
		pr_err("No valid devices specified\n");
		goto err_free_gc;
	}

	gc_base[port_idx] = gc;
	return;

 err_unreg_devs:
	while (--i >= 0)
		if (gc->pads[i].dev)
			input_unregister_device(gc->pads[i].dev);
 err_free_gc:
	kfree(gc);
 err_unreg_pardev:
	parport_unregister_device(pd);
}