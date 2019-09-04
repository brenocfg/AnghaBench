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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct eth_rss_update_ramrod_data {int /*<<< orphan*/  indirection_table; int /*<<< orphan*/  rss_engine_id; int /*<<< orphan*/  rss_result_mask; int /*<<< orphan*/  capabilities; scalar_t__ rss_key; int /*<<< orphan*/  rss_mode; int /*<<< orphan*/  echo; } ;
struct bnx2x_raw_obj {int cid; int state; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x_rss_config_obj {int /*<<< orphan*/  ind_table; int /*<<< orphan*/  engine_id; struct bnx2x_raw_obj raw; } ;
struct bnx2x_config_rss_params {int /*<<< orphan*/  ind_table; int /*<<< orphan*/  rss_result_mask; scalar_t__ rss_key; int /*<<< orphan*/  rss_flags; struct bnx2x_rss_config_obj* rss_obj; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_VXLAN ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_VXLAN ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_DISABLED ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_REGULAR ; 
 int /*<<< orphan*/  BNX2X_RSS_SET_SRCH ; 
 int /*<<< orphan*/  BNX2X_RSS_TUNN_INNER_HDRS ; 
 int BNX2X_SWCID_MASK ; 
 int BNX2X_SWCID_SHIFT ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  ETH_RSS_MODE_DISABLED ; 
 int /*<<< orphan*/  ETH_RSS_MODE_REGULAR ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV4_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV4_TCP_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV4_UDP_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV4_VXLAN_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV6_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV6_TCP_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV6_UDP_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_IPV6_VXLAN_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_TUNN_INNER_HDRS_CAPABILITY ; 
 int /*<<< orphan*/  ETH_RSS_UPDATE_RAMROD_DATA_UPDATE_RSS_KEY ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_RSS_UPDATE ; 
 int /*<<< orphan*/  T_ETH_INDIRECTION_TABLE_SIZE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_debug_print_ind_table (struct bnx2x*,struct bnx2x_config_rss_params*) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct eth_rss_update_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_ifup (struct bnx2x*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_setup_rss(struct bnx2x *bp,
			   struct bnx2x_config_rss_params *p)
{
	struct bnx2x_rss_config_obj *o = p->rss_obj;
	struct bnx2x_raw_obj *r = &o->raw;
	struct eth_rss_update_ramrod_data *data =
		(struct eth_rss_update_ramrod_data *)(r->rdata);
	u16 caps = 0;
	u8 rss_mode = 0;
	int rc;

	memset(data, 0, sizeof(*data));

	DP(BNX2X_MSG_SP, "Configuring RSS\n");

	/* Set an echo field */
	data->echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				 (r->state << BNX2X_SWCID_SHIFT));

	/* RSS mode */
	if (test_bit(BNX2X_RSS_MODE_DISABLED, &p->rss_flags))
		rss_mode = ETH_RSS_MODE_DISABLED;
	else if (test_bit(BNX2X_RSS_MODE_REGULAR, &p->rss_flags))
		rss_mode = ETH_RSS_MODE_REGULAR;

	data->rss_mode = rss_mode;

	DP(BNX2X_MSG_SP, "rss_mode=%d\n", rss_mode);

	/* RSS capabilities */
	if (test_bit(BNX2X_RSS_IPV4, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV4_TCP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_TCP_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV4_UDP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_UDP_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV6, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV6_TCP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_TCP_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV6_UDP, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_UDP_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV4_VXLAN, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV4_VXLAN_CAPABILITY;

	if (test_bit(BNX2X_RSS_IPV6_VXLAN, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_IPV6_VXLAN_CAPABILITY;

	if (test_bit(BNX2X_RSS_TUNN_INNER_HDRS, &p->rss_flags))
		caps |= ETH_RSS_UPDATE_RAMROD_DATA_TUNN_INNER_HDRS_CAPABILITY;

	/* RSS keys */
	if (test_bit(BNX2X_RSS_SET_SRCH, &p->rss_flags)) {
		u8 *dst = (u8 *)(data->rss_key) + sizeof(data->rss_key);
		const u8 *src = (const u8 *)p->rss_key;
		int i;

		/* Apparently, bnx2x reads this array in reverse order
		 * We need to byte swap rss_key to comply with Toeplitz specs.
		 */
		for (i = 0; i < sizeof(data->rss_key); i++)
			*--dst = *src++;

		caps |= ETH_RSS_UPDATE_RAMROD_DATA_UPDATE_RSS_KEY;
	}

	data->capabilities = cpu_to_le16(caps);

	/* Hashing mask */
	data->rss_result_mask = p->rss_result_mask;

	/* RSS engine ID */
	data->rss_engine_id = o->engine_id;

	DP(BNX2X_MSG_SP, "rss_engine_id=%d\n", data->rss_engine_id);

	/* Indirection table */
	memcpy(data->indirection_table, p->ind_table,
		  T_ETH_INDIRECTION_TABLE_SIZE);

	/* Remember the last configuration */
	memcpy(o->ind_table, p->ind_table, T_ETH_INDIRECTION_TABLE_SIZE);

	/* Print the indirection table */
	if (netif_msg_ifup(bp))
		bnx2x_debug_print_ind_table(bp, p);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */

	/* Send a ramrod */
	rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_RSS_UPDATE, r->cid,
			   U64_HI(r->rdata_mapping),
			   U64_LO(r->rdata_mapping),
			   ETH_CONNECTION_TYPE);

	if (rc < 0)
		return rc;

	return 1;
}