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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct nix_rx_flowkey_alg {int sel_chan; int bytesm1; int ltype_match; int hdr_offset; int ltype_mask; int ena; int key_offset; void* lid; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int FIELDS_PER_ALG ; 
 int MAX_KEY_OFF ; 
 int NIX_AF_ERR_RSS_NOSPC_FIELD ; 
#define  NIX_FLOW_KEY_TYPE_IPV4 133 
#define  NIX_FLOW_KEY_TYPE_IPV6 132 
#define  NIX_FLOW_KEY_TYPE_PORT 131 
#define  NIX_FLOW_KEY_TYPE_SCTP 130 
#define  NIX_FLOW_KEY_TYPE_TCP 129 
#define  NIX_FLOW_KEY_TYPE_UDP 128 
 void* NPC_LID_LC ; 
 void* NPC_LID_LD ; 
 int NPC_LT_LC_IP ; 
 int NPC_LT_LC_IP6 ; 
 int NPC_LT_LD_SCTP ; 
 int NPC_LT_LD_TCP ; 
 int NPC_LT_LD_UDP ; 
 int fls (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (struct nix_rx_flowkey_alg*,struct nix_rx_flowkey_alg*,int) ; 
 int /*<<< orphan*/  memset (struct nix_rx_flowkey_alg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_flowkey_fields(struct nix_rx_flowkey_alg *alg, u32 flow_cfg)
{
	int idx, nr_field, key_off, field_marker, keyoff_marker;
	int max_key_off, max_bit_pos, group_member;
	struct nix_rx_flowkey_alg *field;
	struct nix_rx_flowkey_alg tmp;
	u32 key_type, valid_key;

	if (!alg)
		return -EINVAL;

#define FIELDS_PER_ALG  5
#define MAX_KEY_OFF	40
	/* Clear all fields */
	memset(alg, 0, sizeof(uint64_t) * FIELDS_PER_ALG);

	/* Each of the 32 possible flow key algorithm definitions should
	 * fall into above incremental config (except ALG0). Otherwise a
	 * single NPC MCAM entry is not sufficient for supporting RSS.
	 *
	 * If a different definition or combination needed then NPC MCAM
	 * has to be programmed to filter such pkts and it's action should
	 * point to this definition to calculate flowtag or hash.
	 *
	 * The `for loop` goes over _all_ protocol field and the following
	 * variables depicts the state machine forward progress logic.
	 *
	 * keyoff_marker - Enabled when hash byte length needs to be accounted
	 * in field->key_offset update.
	 * field_marker - Enabled when a new field needs to be selected.
	 * group_member - Enabled when protocol is part of a group.
	 */

	keyoff_marker = 0; max_key_off = 0; group_member = 0;
	nr_field = 0; key_off = 0; field_marker = 1;
	field = &tmp; max_bit_pos = fls(flow_cfg);
	for (idx = 0;
	     idx < max_bit_pos && nr_field < FIELDS_PER_ALG &&
	     key_off < MAX_KEY_OFF; idx++) {
		key_type = BIT(idx);
		valid_key = flow_cfg & key_type;
		/* Found a field marker, reset the field values */
		if (field_marker)
			memset(&tmp, 0, sizeof(tmp));

		switch (key_type) {
		case NIX_FLOW_KEY_TYPE_PORT:
			field->sel_chan = true;
			/* This should be set to 1, when SEL_CHAN is set */
			field->bytesm1 = 1;
			field_marker = true;
			keyoff_marker = true;
			break;
		case NIX_FLOW_KEY_TYPE_IPV4:
			field->lid = NPC_LID_LC;
			field->ltype_match = NPC_LT_LC_IP;
			field->hdr_offset = 12; /* SIP offset */
			field->bytesm1 = 7; /* SIP + DIP, 8 bytes */
			field->ltype_mask = 0xF; /* Match only IPv4 */
			field_marker = true;
			keyoff_marker = false;
			break;
		case NIX_FLOW_KEY_TYPE_IPV6:
			field->lid = NPC_LID_LC;
			field->ltype_match = NPC_LT_LC_IP6;
			field->hdr_offset = 8; /* SIP offset */
			field->bytesm1 = 31; /* SIP + DIP, 32 bytes */
			field->ltype_mask = 0xF; /* Match only IPv6 */
			field_marker = true;
			keyoff_marker = true;
			break;
		case NIX_FLOW_KEY_TYPE_TCP:
		case NIX_FLOW_KEY_TYPE_UDP:
		case NIX_FLOW_KEY_TYPE_SCTP:
			field->lid = NPC_LID_LD;
			field->bytesm1 = 3; /* Sport + Dport, 4 bytes */
			if (key_type == NIX_FLOW_KEY_TYPE_TCP && valid_key) {
				field->ltype_match |= NPC_LT_LD_TCP;
				group_member = true;
			} else if (key_type == NIX_FLOW_KEY_TYPE_UDP &&
				   valid_key) {
				field->ltype_match |= NPC_LT_LD_UDP;
				group_member = true;
			} else if (key_type == NIX_FLOW_KEY_TYPE_SCTP &&
				   valid_key) {
				field->ltype_match |= NPC_LT_LD_SCTP;
				group_member = true;
			}
			field->ltype_mask = ~field->ltype_match;
			if (key_type == NIX_FLOW_KEY_TYPE_SCTP) {
				/* Handle the case where any of the group item
				 * is enabled in the group but not the final one
				 */
				if (group_member) {
					valid_key = true;
					group_member = false;
				}
				field_marker = true;
				keyoff_marker = true;
			} else {
				field_marker = false;
				keyoff_marker = false;
			}
			break;
		}
		field->ena = 1;

		/* Found a valid flow key type */
		if (valid_key) {
			field->key_offset = key_off;
			memcpy(&alg[nr_field], field, sizeof(*field));
			max_key_off = max(max_key_off, field->bytesm1 + 1);

			/* Found a field marker, get the next field */
			if (field_marker)
				nr_field++;
		}

		/* Found a keyoff marker, update the new key_off */
		if (keyoff_marker) {
			key_off += max_key_off;
			max_key_off = 0;
		}
	}
	/* Processed all the flow key types */
	if (idx == max_bit_pos && key_off <= MAX_KEY_OFF)
		return 0;
	else
		return NIX_AF_ERR_RSS_NOSPC_FIELD;
}