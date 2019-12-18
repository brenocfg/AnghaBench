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
struct pps_source_info {char* path; int mode; int /*<<< orphan*/ * dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct pps_client_pp {int index; int /*<<< orphan*/  pardev; int /*<<< orphan*/  cw; int /*<<< orphan*/  pps; } ;
struct parport {int /*<<< orphan*/  name; TYPE_1__* ops; } ;
struct pardev_cb {int /*<<< orphan*/  flags; int /*<<< orphan*/  irq_func; struct pps_client_pp* private; } ;
typedef  int /*<<< orphan*/  pps_client_cb ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_irq ) (struct parport*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PARPORT_FLAG_EXCL ; 
 int PPS_CANWAIT ; 
 int PPS_CAPTUREBOTH ; 
 int PPS_ECHOASSERT ; 
 int PPS_ECHOCLEAR ; 
 int PPS_OFFSETASSERT ; 
 int PPS_OFFSETCLEAR ; 
 int PPS_TSFMT_TSPEC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clear_wait ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct pps_client_pp*) ; 
 struct pps_client_pp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parport_claim_or_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_irq ; 
 int /*<<< orphan*/  parport_register_dev_model (struct parport*,int /*<<< orphan*/ ,struct pardev_cb*,int) ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_client_index ; 
 int /*<<< orphan*/  pps_register_source (struct pps_source_info*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct parport*) ; 

__attribute__((used)) static void parport_attach(struct parport *port)
{
	struct pardev_cb pps_client_cb;
	int index;
	struct pps_client_pp *device;
	struct pps_source_info info = {
		.name		= KBUILD_MODNAME,
		.path		= "",
		.mode		= PPS_CAPTUREBOTH | \
				  PPS_OFFSETASSERT | PPS_OFFSETCLEAR | \
				  PPS_ECHOASSERT | PPS_ECHOCLEAR | \
				  PPS_CANWAIT | PPS_TSFMT_TSPEC,
		.owner		= THIS_MODULE,
		.dev		= NULL
	};

	device = kzalloc(sizeof(struct pps_client_pp), GFP_KERNEL);
	if (!device) {
		pr_err("memory allocation failed, not attaching\n");
		return;
	}

	index = ida_simple_get(&pps_client_index, 0, 0, GFP_KERNEL);
	memset(&pps_client_cb, 0, sizeof(pps_client_cb));
	pps_client_cb.private = device;
	pps_client_cb.irq_func = parport_irq;
	pps_client_cb.flags = PARPORT_FLAG_EXCL;
	device->pardev = parport_register_dev_model(port,
						    KBUILD_MODNAME,
						    &pps_client_cb,
						    index);
	if (!device->pardev) {
		pr_err("couldn't register with %s\n", port->name);
		goto err_free;
	}

	if (parport_claim_or_block(device->pardev) < 0) {
		pr_err("couldn't claim %s\n", port->name);
		goto err_unregister_dev;
	}

	device->pps = pps_register_source(&info,
			PPS_CAPTUREBOTH | PPS_OFFSETASSERT | PPS_OFFSETCLEAR);
	if (IS_ERR(device->pps)) {
		pr_err("couldn't register PPS source\n");
		goto err_release_dev;
	}

	device->cw = clear_wait;

	port->ops->enable_irq(port);
	device->index = index;

	pr_info("attached to %s\n", port->name);

	return;

err_release_dev:
	parport_release(device->pardev);
err_unregister_dev:
	parport_unregister_device(device->pardev);
err_free:
	ida_simple_remove(&pps_client_index, index);
	kfree(device);
}