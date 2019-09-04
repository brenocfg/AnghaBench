#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct parport {scalar_t__ base; } ;
struct pardev_cb {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ks0108_cb ;

/* Variables and functions */
 int /*<<< orphan*/  KS0108_NAME ; 
 int /*<<< orphan*/  PARPORT_DEV_EXCL ; 
 int ks0108_inited ; 
 int /*<<< orphan*/ * ks0108_pardevice ; 
 struct parport* ks0108_parport ; 
 scalar_t__ ks0108_port ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parport_claim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parport_register_dev_model (struct parport*,int /*<<< orphan*/ ,struct pardev_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void ks0108_parport_attach(struct parport *port)
{
	struct pardev_cb ks0108_cb;

	if (port->base != ks0108_port)
		return;

	memset(&ks0108_cb, 0, sizeof(ks0108_cb));
	ks0108_cb.flags = PARPORT_DEV_EXCL;
	ks0108_pardevice = parport_register_dev_model(port, KS0108_NAME,
						      &ks0108_cb, 0);
	if (!ks0108_pardevice) {
		pr_err("ERROR: parport didn't register new device\n");
		return;
	}
	if (parport_claim(ks0108_pardevice)) {
		pr_err("could not claim access to parport %i. Aborting.\n",
		       ks0108_port);
		goto err_unreg_device;
	}

	ks0108_parport = port;
	ks0108_inited = 1;
	return;

err_unreg_device:
	parport_unregister_device(ks0108_pardevice);
	ks0108_pardevice = NULL;
}