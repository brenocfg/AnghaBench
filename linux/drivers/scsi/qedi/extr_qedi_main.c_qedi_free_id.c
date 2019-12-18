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
typedef  scalar_t__ u16 ;
struct qedi_portid_tbl {scalar_t__ start; scalar_t__ max; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ QEDI_LOCAL_PORT_INVALID ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

void qedi_free_id(struct qedi_portid_tbl *id_tbl, u16 id)
{
	if (id == QEDI_LOCAL_PORT_INVALID)
		return;

	id -= id_tbl->start;
	if (id >= id_tbl->max)
		return;

	clear_bit(id, id_tbl->table);
}