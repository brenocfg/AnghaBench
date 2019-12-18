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
typedef  int u32 ;

/* Variables and functions */
#define  MVPP22_CLS_HEK_OPT_IP4DA 136 
#define  MVPP22_CLS_HEK_OPT_IP4SA 135 
#define  MVPP22_CLS_HEK_OPT_IP6DA 134 
#define  MVPP22_CLS_HEK_OPT_IP6SA 133 
#define  MVPP22_CLS_HEK_OPT_L4DIP 132 
#define  MVPP22_CLS_HEK_OPT_L4SIP 131 
#define  MVPP22_CLS_HEK_OPT_MAC_DA 130 
#define  MVPP22_CLS_HEK_OPT_VLAN 129 
#define  MVPP22_CLS_HEK_OPT_VLAN_PRI 128 

__attribute__((used)) static int mvpp2_cls_hek_field_size(u32 field)
{
	switch (field) {
	case MVPP22_CLS_HEK_OPT_MAC_DA:
		return 48;
	case MVPP22_CLS_HEK_OPT_VLAN:
		return 12;
	case MVPP22_CLS_HEK_OPT_VLAN_PRI:
		return 3;
	case MVPP22_CLS_HEK_OPT_IP4SA:
	case MVPP22_CLS_HEK_OPT_IP4DA:
		return 32;
	case MVPP22_CLS_HEK_OPT_IP6SA:
	case MVPP22_CLS_HEK_OPT_IP6DA:
		return 128;
	case MVPP22_CLS_HEK_OPT_L4SIP:
	case MVPP22_CLS_HEK_OPT_L4DIP:
		return 16;
	default:
		return -1;
	}
}