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
struct zfcp_port {scalar_t__ supported_classes; int /*<<< orphan*/  list; int /*<<< orphan*/  unit_list; int /*<<< orphan*/  status; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_NOESC ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void zfcp_fc_validate_port(struct zfcp_port *port, struct list_head *lh)
{
	if (!(atomic_read(&port->status) & ZFCP_STATUS_COMMON_NOESC))
		return;

	atomic_andnot(ZFCP_STATUS_COMMON_NOESC, &port->status);

	if ((port->supported_classes != 0) ||
	    !list_empty(&port->unit_list))
		return;

	list_move_tail(&port->list, lh);
}