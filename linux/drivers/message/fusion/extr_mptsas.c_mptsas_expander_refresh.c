#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct sas_rphy {struct device dev; } ;
struct mptsas_portinfo {int num_phys; TYPE_4__* phy_info; } ;
struct TYPE_13__ {scalar_t__ sas_address; int /*<<< orphan*/  handle_parent; int /*<<< orphan*/  phy_id; scalar_t__ handle; } ;
struct TYPE_12__ {TYPE_6__ attached; TYPE_6__ identify; int /*<<< orphan*/  phy_id; scalar_t__ handle; } ;
struct TYPE_11__ {int /*<<< orphan*/  sas_index; int /*<<< orphan*/  sas_topology_mutex; } ;
typedef  TYPE_1__ MPT_ADAPTER ;

/* Variables and functions */
 int MPI_SAS_DEVICE_PGAD_FORM_HANDLE ; 
 int MPI_SAS_DEVICE_PGAD_FORM_SHIFT ; 
 int MPI_SAS_EXPAND_PGAD_FORM_HANDLE_PHY_NUM ; 
 int MPI_SAS_EXPAND_PGAD_FORM_SHIFT ; 
 struct mptsas_portinfo* mptsas_find_portinfo_by_handle (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sas_rphy* mptsas_get_rphy (TYPE_4__*) ; 
 int /*<<< orphan*/  mptsas_probe_one_phy (struct device*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptsas_sas_device_pg0 (TYPE_1__*,TYPE_6__*,int,scalar_t__) ; 
 int /*<<< orphan*/  mptsas_sas_expander_pg1 (TYPE_1__*,TYPE_4__*,int,scalar_t__) ; 
 int /*<<< orphan*/  mptsas_setup_wide_ports (TYPE_1__*,struct mptsas_portinfo*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mptsas_expander_refresh(MPT_ADAPTER *ioc, struct mptsas_portinfo *port_info)
{
	struct mptsas_portinfo *parent;
	struct device *parent_dev;
	struct sas_rphy	*rphy;
	int		i;
	u64		sas_address; /* expander sas address */
	u32		handle;

	handle = port_info->phy_info[0].handle;
	sas_address = port_info->phy_info[0].identify.sas_address;
	for (i = 0; i < port_info->num_phys; i++) {
		mptsas_sas_expander_pg1(ioc, &port_info->phy_info[i],
		    (MPI_SAS_EXPAND_PGAD_FORM_HANDLE_PHY_NUM <<
		    MPI_SAS_EXPAND_PGAD_FORM_SHIFT), (i << 16) + handle);

		mptsas_sas_device_pg0(ioc,
		    &port_info->phy_info[i].identify,
		    (MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
		    MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
		    port_info->phy_info[i].identify.handle);
		port_info->phy_info[i].identify.phy_id =
		    port_info->phy_info[i].phy_id;

		if (port_info->phy_info[i].attached.handle) {
			mptsas_sas_device_pg0(ioc,
			    &port_info->phy_info[i].attached,
			    (MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
			     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			    port_info->phy_info[i].attached.handle);
			port_info->phy_info[i].attached.phy_id =
			    port_info->phy_info[i].phy_id;
		}
	}

	mutex_lock(&ioc->sas_topology_mutex);
	parent = mptsas_find_portinfo_by_handle(ioc,
	    port_info->phy_info[0].identify.handle_parent);
	if (!parent) {
		mutex_unlock(&ioc->sas_topology_mutex);
		return;
	}
	for (i = 0, parent_dev = NULL; i < parent->num_phys && !parent_dev;
	    i++) {
		if (parent->phy_info[i].attached.sas_address == sas_address) {
			rphy = mptsas_get_rphy(&parent->phy_info[i]);
			parent_dev = &rphy->dev;
		}
	}
	mutex_unlock(&ioc->sas_topology_mutex);

	mptsas_setup_wide_ports(ioc, port_info);
	for (i = 0; i < port_info->num_phys; i++, ioc->sas_index++)
		mptsas_probe_one_phy(parent_dev, &port_info->phy_info[i],
		    ioc->sas_index, 0);
}