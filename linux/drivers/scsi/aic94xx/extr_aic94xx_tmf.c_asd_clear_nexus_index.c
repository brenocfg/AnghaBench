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
struct sas_task {TYPE_4__* dev; struct asd_ascb* lldd_task; } ;
struct asd_ha_struct {int dummy; } ;
struct asd_ascb {int /*<<< orphan*/  tc_index; } ;
struct TYPE_6__ {void* index; void* conn_handle; int /*<<< orphan*/  nexus; } ;
struct TYPE_10__ {TYPE_1__ clear_nexus; } ;
struct TYPE_9__ {scalar_t__ lldd_dev; scalar_t__ tproto; TYPE_3__* port; } ;
struct TYPE_8__ {TYPE_2__* ha; } ;
struct TYPE_7__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_NEXUS_POST ; 
 int /*<<< orphan*/  CLEAR_NEXUS_PRE ; 
 int /*<<< orphan*/  NEXUS_TRANS_CX ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_5__* scb ; 

__attribute__((used)) static int asd_clear_nexus_index(struct sas_task *task)
{
	struct asd_ha_struct *asd_ha = task->dev->port->ha->lldd_ha;
	struct asd_ascb *tascb = task->lldd_task;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_TRANS_CX;
	if (task->dev->tproto)
		scb->clear_nexus.conn_handle = cpu_to_le16((u16)(unsigned long)
							  task->dev->lldd_dev);
	scb->clear_nexus.index = cpu_to_le16(tascb->tc_index);
	CLEAR_NEXUS_POST;
}