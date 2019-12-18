#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int vlan_pri_map; } ;
struct TYPE_4__ {TYPE_1__ tp; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
#define  ETHERTYPE_F 137 
#define  FCOE_F 136 
#define  FRAGMENTATION_F 135 
 int FT_ETHERTYPE_W ; 
 int FT_FCOE_W ; 
 int FT_FRAGMENTATION_W ; 
 int FT_MACMATCH_W ; 
 int FT_MPSHITTYPE_W ; 
 int FT_PORT_W ; 
 int FT_PROTOCOL_W ; 
 int FT_TOS_W ; 
 int FT_VLAN_W ; 
 int FT_VNIC_ID_W ; 
#define  MACMATCH_F 134 
#define  MPSHITTYPE_F 133 
#define  PORT_F 132 
#define  PROTOCOL_F 131 
#define  TOS_F 130 
#define  VLAN_F 129 
#define  VNIC_ID_F 128 

int t4_filter_field_shift(const struct adapter *adap, int filter_sel)
{
	unsigned int filter_mode = adap->params.tp.vlan_pri_map;
	unsigned int sel;
	int field_shift;

	if ((filter_mode & filter_sel) == 0)
		return -1;

	for (sel = 1, field_shift = 0; sel < filter_sel; sel <<= 1) {
		switch (filter_mode & sel) {
		case FCOE_F:
			field_shift += FT_FCOE_W;
			break;
		case PORT_F:
			field_shift += FT_PORT_W;
			break;
		case VNIC_ID_F:
			field_shift += FT_VNIC_ID_W;
			break;
		case VLAN_F:
			field_shift += FT_VLAN_W;
			break;
		case TOS_F:
			field_shift += FT_TOS_W;
			break;
		case PROTOCOL_F:
			field_shift += FT_PROTOCOL_W;
			break;
		case ETHERTYPE_F:
			field_shift += FT_ETHERTYPE_W;
			break;
		case MACMATCH_F:
			field_shift += FT_MACMATCH_W;
			break;
		case MPSHITTYPE_F:
			field_shift += FT_MPSHITTYPE_W;
			break;
		case FRAGMENTATION_F:
			field_shift += FT_FRAGMENTATION_W;
			break;
		}
	}
	return field_shift;
}