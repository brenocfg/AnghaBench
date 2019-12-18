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
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int /*<<< orphan*/  tx_rings; } ;
typedef  enum ice_disq_rst_src { ____Placeholder_ice_disq_rst_src } ice_disq_rst_src ;

/* Variables and functions */
 int ice_vsi_stop_tx_rings (struct ice_vsi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ice_vsi_stop_lan_tx_rings(struct ice_vsi *vsi, enum ice_disq_rst_src rst_src,
			  u16 rel_vmvf_num)
{
	return ice_vsi_stop_tx_rings(vsi, rst_src, rel_vmvf_num, vsi->tx_rings);
}