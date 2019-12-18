#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mptsas_portinfo {int num_phys; TYPE_2__* phy_info; } ;
struct fw_event_work {scalar_t__ event_data; int /*<<< orphan*/ * ioc; } ;
typedef  void* __le64 ;
struct TYPE_7__ {scalar_t__ ReasonCode; scalar_t__ NumPhys; int /*<<< orphan*/  ParentDevHandle; int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  SASAddress; } ;
struct TYPE_5__ {void* handle_parent; void* sas_address; } ;
struct TYPE_6__ {TYPE_1__ identify; void* handle; struct mptsas_portinfo* portinfo; } ;
typedef  TYPE_3__ MpiEventDataSasExpanderStatusChange_t ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 scalar_t__ MPI_EVENT_SAS_EXP_RC_ADDED ; 
 scalar_t__ MPI_EVENT_SAS_EXP_RC_NOT_RESPONDING ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mptsas_expander_delete (int /*<<< orphan*/ *,struct mptsas_portinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptsas_expander_event_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mptsas_expander_refresh (int /*<<< orphan*/ *,struct mptsas_portinfo*) ; 
 struct mptsas_portinfo* mptsas_find_portinfo_by_sas_address (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mptsas_free_fw_event (int /*<<< orphan*/ *,struct fw_event_work*) ; 

__attribute__((used)) static void
mptsas_send_expander_event(struct fw_event_work *fw_event)
{
	MPT_ADAPTER *ioc;
	MpiEventDataSasExpanderStatusChange_t *expander_data;
	struct mptsas_portinfo *port_info;
	__le64 sas_address;
	int i;

	ioc = fw_event->ioc;
	expander_data = (MpiEventDataSasExpanderStatusChange_t *)
	    fw_event->event_data;
	memcpy(&sas_address, &expander_data->SASAddress, sizeof(__le64));
	sas_address = le64_to_cpu(sas_address);
	port_info = mptsas_find_portinfo_by_sas_address(ioc, sas_address);

	if (expander_data->ReasonCode == MPI_EVENT_SAS_EXP_RC_ADDED) {
		if (port_info) {
			for (i = 0; i < port_info->num_phys; i++) {
				port_info->phy_info[i].portinfo = port_info;
				port_info->phy_info[i].handle =
				    le16_to_cpu(expander_data->DevHandle);
				port_info->phy_info[i].identify.sas_address =
				    le64_to_cpu(sas_address);
				port_info->phy_info[i].identify.handle_parent =
				    le16_to_cpu(expander_data->ParentDevHandle);
			}
			mptsas_expander_refresh(ioc, port_info);
		} else if (!port_info && expander_data->NumPhys)
			mptsas_expander_event_add(ioc, expander_data);
	} else if (expander_data->ReasonCode ==
	    MPI_EVENT_SAS_EXP_RC_NOT_RESPONDING)
		mptsas_expander_delete(ioc, port_info, 0);

	mptsas_free_fw_event(ioc, fw_event);
}