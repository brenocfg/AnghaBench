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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_unit {int dummy; } ;
struct zfcp_port {int /*<<< orphan*/  unit_list_lock; } ;

/* Variables and functions */
 struct zfcp_unit* _zfcp_unit_find (struct zfcp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 

struct zfcp_unit *zfcp_unit_find(struct zfcp_port *port, u64 fcp_lun)
{
	struct zfcp_unit *unit;

	read_lock_irq(&port->unit_list_lock);
	unit = _zfcp_unit_find(port, fcp_lun);
	read_unlock_irq(&port->unit_list_lock);
	return unit;
}