#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cmng_vnic {TYPE_3__* vnic_max_rate; } ;
struct TYPE_4__ {int rs_periodic_timeout; int rs_threshold; } ;
struct cmng_struct_per_port {TYPE_1__ rs_vars; } ;
struct cmng_init_input {scalar_t__* vnic_max_rate; } ;
struct cmng_init {struct cmng_struct_per_port port; struct cmng_vnic vnic; } ;
struct TYPE_5__ {int quota; scalar_t__ rate; } ;
struct TYPE_6__ {TYPE_2__ vn_counter; } ;

/* Variables and functions */
 int BNX2X_PORT2_MODE_NUM_VNICS ; 
 int RS_PERIODIC_TIMEOUT_USEC ; 
 int SDM_TICKS ; 

__attribute__((used)) static inline void bnx2x_init_max(const struct cmng_init_input *input_data,
				  u32 r_param, struct cmng_init *ram_data)
{
	u32 vnic;
	struct cmng_vnic *vdata = &ram_data->vnic;
	struct cmng_struct_per_port *pdata = &ram_data->port;
	/* rate shaping per-port variables
	 * 100 micro seconds in SDM ticks = 25
	 * since each tick is 4 microSeconds
	 */

	pdata->rs_vars.rs_periodic_timeout =
	RS_PERIODIC_TIMEOUT_USEC / SDM_TICKS;

	/* this is the threshold below which no timer arming will occur.
	 * 1.25 coefficient is for the threshold to be a little bigger
	 * then the real time to compensate for timer in-accuracy
	 */
	pdata->rs_vars.rs_threshold =
	(5 * RS_PERIODIC_TIMEOUT_USEC * r_param)/4;

	/* rate shaping per-vnic variables */
	for (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) {
		/* global vnic counter */
		vdata->vnic_max_rate[vnic].vn_counter.rate =
		input_data->vnic_max_rate[vnic];
		/* maximal Mbps for this vnic
		 * the quota in each timer period - number of bytes
		 * transmitted in this period
		 */
		vdata->vnic_max_rate[vnic].vn_counter.quota =
			RS_PERIODIC_TIMEOUT_USEC *
			(u32)vdata->vnic_max_rate[vnic].vn_counter.rate / 8;
	}

}