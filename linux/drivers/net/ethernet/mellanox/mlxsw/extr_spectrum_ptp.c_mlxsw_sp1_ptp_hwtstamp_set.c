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
typedef  void* u16 ;
struct hwtstamp_config {int rx_filter; } ;
struct TYPE_2__ {void* egr_types; void* ing_types; struct hwtstamp_config hwtstamp_config; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;
typedef  enum hwtstamp_rx_filters { ____Placeholder_hwtstamp_rx_filters } hwtstamp_rx_filters ;

/* Variables and functions */
 int mlxsw_sp1_ptp_mtpppc_update (struct mlxsw_sp_port*,void*,void*) ; 
 int mlxsw_sp1_ptp_port_shaper_check (struct mlxsw_sp_port*) ; 
 int mlxsw_sp_ptp_get_message_types (struct hwtstamp_config*,void**,void**,int*) ; 

int mlxsw_sp1_ptp_hwtstamp_set(struct mlxsw_sp_port *mlxsw_sp_port,
			       struct hwtstamp_config *config)
{
	enum hwtstamp_rx_filters rx_filter;
	u16 ing_types;
	u16 egr_types;
	int err;

	err = mlxsw_sp_ptp_get_message_types(config, &ing_types, &egr_types,
					     &rx_filter);
	if (err)
		return err;

	err = mlxsw_sp1_ptp_mtpppc_update(mlxsw_sp_port, ing_types, egr_types);
	if (err)
		return err;

	mlxsw_sp_port->ptp.hwtstamp_config = *config;
	mlxsw_sp_port->ptp.ing_types = ing_types;
	mlxsw_sp_port->ptp.egr_types = egr_types;

	err = mlxsw_sp1_ptp_port_shaper_check(mlxsw_sp_port);
	if (err)
		return err;

	/* Notify the ioctl caller what we are actually timestamping. */
	config->rx_filter = rx_filter;

	return 0;
}