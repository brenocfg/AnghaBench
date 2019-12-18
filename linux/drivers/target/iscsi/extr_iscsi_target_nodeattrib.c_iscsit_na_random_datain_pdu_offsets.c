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
struct iscsi_node_attrib {int random_datain_pdu_offsets; } ;
struct iscsi_node_acl {struct iscsi_node_attrib node_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iscsit_na_get_initiatorname (struct iscsi_node_acl*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int iscsit_na_random_datain_pdu_offsets(
	struct iscsi_node_acl *acl,
	u32 random_datain_pdu_offsets)
{
	struct iscsi_node_attrib *a = &acl->node_attrib;

	if (random_datain_pdu_offsets != 0 && random_datain_pdu_offsets != 1) {
		pr_err("Requested Random DataIN PDU Offsets: %u not"
			" 0 or 1\n", random_datain_pdu_offsets);
		return -EINVAL;
	}

	a->random_datain_pdu_offsets = random_datain_pdu_offsets;
	pr_debug("Set Random DataIN PDU Offsets to %u for"
		" Initiator Node %s\n", a->random_datain_pdu_offsets,
		iscsit_na_get_initiatorname(acl));

	return 0;
}