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

/* Variables and functions */
 int /*<<< orphan*/  KS0108_NAME ; 
 int /*<<< orphan*/ * ks0108_pardevice ; 
 int /*<<< orphan*/ * ks0108_parport ; 
 scalar_t__ ks0108_port ; 
 int /*<<< orphan*/  parport_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks0108_parport_detach(struct parport *port)
{
	if (port->base != ks0108_port)
		return;

	if (!ks0108_pardevice) {
		pr_err("%s: already unregistered.\n", KS0108_NAME);
		return;
	}

	parport_release(ks0108_pardevice);
	parport_unregister_device(ks0108_pardevice);
	ks0108_pardevice = NULL;
	ks0108_parport = NULL;
}