#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int InitiatorDeviceTimeout; int InitiatorIoPendTimeout; int Flags; } ;
struct TYPE_11__ {TYPE_2__* fc_port_page1; } ;
struct TYPE_9__ {int NumberOfPorts; } ;
struct TYPE_12__ {TYPE_3__ fc_data; TYPE_1__ facts; } ;
struct TYPE_10__ {TYPE_5__* data; } ;
typedef  TYPE_4__ MPT_ADAPTER ;
typedef  TYPE_5__ FCPortPage1_t ;

/* Variables and functions */
 int MPI_FCPORTPAGE1_FLAGS_IMMEDIATE_ERROR_REPLY ; 
 int MPI_FCPORTPAGE1_FLAGS_VERBOSE_RESCAN_EVENTS ; 
 scalar_t__ mptfc_GetFcPortPage1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mptfc_WriteFcPortPage1 (TYPE_4__*,int) ; 

__attribute__((used)) static void
mptfc_SetFcPortPage1_defaults(MPT_ADAPTER *ioc)
{
	int		ii;
	FCPortPage1_t	*pp1;

	#define MPTFC_FW_DEVICE_TIMEOUT	(1)
	#define MPTFC_FW_IO_PEND_TIMEOUT (1)
	#define ON_FLAGS  (MPI_FCPORTPAGE1_FLAGS_IMMEDIATE_ERROR_REPLY)
	#define OFF_FLAGS (MPI_FCPORTPAGE1_FLAGS_VERBOSE_RESCAN_EVENTS)

	for (ii=0; ii<ioc->facts.NumberOfPorts; ii++) {
		if (mptfc_GetFcPortPage1(ioc, ii) != 0)
			continue;
		pp1 = ioc->fc_data.fc_port_page1[ii].data;
		if ((pp1->InitiatorDeviceTimeout == MPTFC_FW_DEVICE_TIMEOUT)
		 && (pp1->InitiatorIoPendTimeout == MPTFC_FW_IO_PEND_TIMEOUT)
		 && ((pp1->Flags & ON_FLAGS) == ON_FLAGS)
		 && ((pp1->Flags & OFF_FLAGS) == 0))
			continue;
		pp1->InitiatorDeviceTimeout = MPTFC_FW_DEVICE_TIMEOUT;
		pp1->InitiatorIoPendTimeout = MPTFC_FW_IO_PEND_TIMEOUT;
		pp1->Flags &= ~OFF_FLAGS;
		pp1->Flags |= ON_FLAGS;
		mptfc_WriteFcPortPage1(ioc, ii);
	}
}