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
struct mvpp2_cls_flow_entry {int dummy; } ;

/* Variables and functions */
#define  MVPP22_CLS_FIELD_IP4DA 137 
#define  MVPP22_CLS_FIELD_IP4SA 136 
#define  MVPP22_CLS_FIELD_IP6DA 135 
#define  MVPP22_CLS_FIELD_IP6SA 134 
#define  MVPP22_CLS_FIELD_L3_PROTO 133 
#define  MVPP22_CLS_FIELD_L4DIP 132 
#define  MVPP22_CLS_FIELD_L4SIP 131 
#define  MVPP22_CLS_FIELD_MAC_DA 130 
#define  MVPP22_CLS_FIELD_VLAN 129 
#define  MVPP22_CLS_FIELD_VLAN_PRI 128 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_IP4DA ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_IP4SA ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_IP6DA ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_IP6SA ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_L3_PROTO ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_L4DIP ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_L4SIP ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_MAC_DA ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_VLAN ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_OPT_VLAN_PRI ; 
 int mvpp2_cls_flow_hek_get (struct mvpp2_cls_flow_entry*,int) ; 
 int mvpp2_cls_flow_hek_num_get (struct mvpp2_cls_flow_entry*) ; 

u16 mvpp2_flow_get_hek_fields(struct mvpp2_cls_flow_entry *fe)
{
	u16 hash_opts = 0;
	int n_fields, i, field;

	n_fields = mvpp2_cls_flow_hek_num_get(fe);

	for (i = 0; i < n_fields; i++) {
		field = mvpp2_cls_flow_hek_get(fe, i);

		switch (field) {
		case MVPP22_CLS_FIELD_MAC_DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_MAC_DA;
			break;
		case MVPP22_CLS_FIELD_VLAN:
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN;
			break;
		case MVPP22_CLS_FIELD_VLAN_PRI:
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN_PRI;
			break;
		case MVPP22_CLS_FIELD_L3_PROTO:
			hash_opts |= MVPP22_CLS_HEK_OPT_L3_PROTO;
			break;
		case MVPP22_CLS_FIELD_IP4SA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP4SA;
			break;
		case MVPP22_CLS_FIELD_IP4DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP4DA;
			break;
		case MVPP22_CLS_FIELD_IP6SA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP6SA;
			break;
		case MVPP22_CLS_FIELD_IP6DA:
			hash_opts |= MVPP22_CLS_HEK_OPT_IP6DA;
			break;
		case MVPP22_CLS_FIELD_L4SIP:
			hash_opts |= MVPP22_CLS_HEK_OPT_L4SIP;
			break;
		case MVPP22_CLS_FIELD_L4DIP:
			hash_opts |= MVPP22_CLS_HEK_OPT_L4DIP;
			break;
		default:
			break;
		}
	}
	return hash_opts;
}