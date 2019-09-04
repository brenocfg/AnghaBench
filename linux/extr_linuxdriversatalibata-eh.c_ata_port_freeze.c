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
struct ata_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ata_port_freeze (struct ata_port*) ; 
 int ata_port_abort (struct ata_port*) ; 

int ata_port_freeze(struct ata_port *ap)
{
	int nr_aborted;

	WARN_ON(!ap->ops->error_handler);

	__ata_port_freeze(ap);
	nr_aborted = ata_port_abort(ap);

	return nr_aborted;
}