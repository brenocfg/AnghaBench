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
struct TYPE_2__ {int numtc; int /*<<< orphan*/  ena_tc; } ;
struct ice_vsi {TYPE_1__ tc_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DFLT_TRAFFIC_CLASS ; 

__attribute__((used)) static inline void ice_vsi_set_tc_cfg(struct ice_vsi *vsi)
{
	vsi->tc_cfg.ena_tc =  ICE_DFLT_TRAFFIC_CLASS;
	vsi->tc_cfg.numtc = 1;
}