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
struct mlxsw_sp_rif {int counter_egress_valid; int counter_ingress_valid; } ;
typedef  enum mlxsw_sp_rif_counter_dir { ____Placeholder_mlxsw_sp_rif_counter_dir } mlxsw_sp_rif_counter_dir ;

/* Variables and functions */
#define  MLXSW_SP_RIF_COUNTER_EGRESS 129 
#define  MLXSW_SP_RIF_COUNTER_INGRESS 128 

__attribute__((used)) static bool
mlxsw_sp_rif_counter_valid_get(struct mlxsw_sp_rif *rif,
			       enum mlxsw_sp_rif_counter_dir dir)
{
	switch (dir) {
	case MLXSW_SP_RIF_COUNTER_EGRESS:
		return rif->counter_egress_valid;
	case MLXSW_SP_RIF_COUNTER_INGRESS:
		return rif->counter_ingress_valid;
	}
	return false;
}