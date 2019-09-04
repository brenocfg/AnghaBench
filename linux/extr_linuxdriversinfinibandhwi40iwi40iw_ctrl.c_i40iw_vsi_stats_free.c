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
typedef  size_t u8 ;
struct i40iw_sc_vsi {size_t fcn_id; TYPE_1__* dev; scalar_t__ stats_fcn_id_alloc; } ;
struct TYPE_2__ {int* fcn_id_array; } ;

/* Variables and functions */
 size_t I40IW_MAX_STATS_COUNT ; 
 int /*<<< orphan*/  i40iw_hw_stats_stop_timer (struct i40iw_sc_vsi*) ; 

void i40iw_vsi_stats_free(struct i40iw_sc_vsi *vsi)
{
	u8 fcn_id = vsi->fcn_id;

	if (vsi->stats_fcn_id_alloc && fcn_id < I40IW_MAX_STATS_COUNT)
		vsi->dev->fcn_id_array[fcn_id] = false;
	i40iw_hw_stats_stop_timer(vsi);
}