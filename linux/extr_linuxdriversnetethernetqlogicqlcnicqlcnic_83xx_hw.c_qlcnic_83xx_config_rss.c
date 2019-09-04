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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_5__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_1__* recv_ctx; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int context_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_CONFIGURE_RSS ; 
 int RSS_HASHTYPE_IP_TCP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_83xx_config_rss(struct qlcnic_adapter *adapter, int enable)
{
	int err;
	u32 word;
	struct qlcnic_cmd_args cmd;
	const u64 key[] = { 0xbeac01fa6a42b73bULL, 0x8030f20c77cb2da3ULL,
			    0xae7b30b4d0ca2bcbULL, 0x43a38fb04167253dULL,
			    0x255b0ec26d5a56daULL };

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIGURE_RSS);
	if (err)
		return err;
	/*
	 * RSS request:
	 * bits 3-0: Rsvd
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enable
	 *        9: use indirection table
	 *    16-31: indirection table mask
	 */
	word =  ((u32)(RSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u32)(RSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u32)(enable & 0x1) << 8) |
		((0x7ULL) << 16);
	cmd.req.arg[1] = (adapter->recv_ctx->context_id);
	cmd.req.arg[2] = word;
	memcpy(&cmd.req.arg[4], key, sizeof(key));

	err = qlcnic_issue_cmd(adapter, &cmd);

	if (err)
		dev_info(&adapter->pdev->dev, "RSS config failed\n");
	qlcnic_free_mbx_args(&cmd);

	return err;

}