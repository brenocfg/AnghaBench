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
struct pnp_dev {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_CONSOLE ; 
 scalar_t__ pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (long) ; 

__attribute__((used)) static void serial_pnp_remove(struct pnp_dev *dev)
{
	long line = (long)pnp_get_drvdata(dev);

	dev->capabilities &= ~PNP_CONSOLE;
	if (line)
		serial8250_unregister_port(line - 1);
}