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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct domain_device {scalar_t__ lldd_dev; TYPE_3__* port; } ;
struct asd_ha_struct {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  conn_handle; TYPE_1__ ssp_task; int /*<<< orphan*/  nexus; } ;
struct TYPE_10__ {TYPE_4__ clear_nexus; } ;
struct TYPE_8__ {TYPE_2__* ha; } ;
struct TYPE_7__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_NEXUS_POST ; 
 int /*<<< orphan*/  CLEAR_NEXUS_PRE ; 
 int EXEC_Q ; 
 int /*<<< orphan*/  NEXUS_I_T_L ; 
 int NOTINQ ; 
 int SEND_Q ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* scb ; 

__attribute__((used)) static int asd_clear_nexus_I_T_L(struct domain_device *dev, u8 *lun)
{
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_I_T_L;
	scb->clear_nexus.flags = SEND_Q | EXEC_Q | NOTINQ;
	memcpy(scb->clear_nexus.ssp_task.lun, lun, 8);
	scb->clear_nexus.conn_handle = cpu_to_le16((u16)(unsigned long)
						   dev->lldd_dev);
	CLEAR_NEXUS_POST;
}