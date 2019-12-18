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
typedef  int u8 ;
typedef  size_t u32 ;
struct ixgbe_adapter {int* rss_indir_tbl; TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int vf_api; int /*<<< orphan*/  rss_query_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  ixgbe_mbox_api_12 130 
#define  ixgbe_mbox_api_13 129 
#define  ixgbe_mbox_api_14 128 
 size_t ixgbe_rss_indir_tbl_entries (struct ixgbe_adapter*) ; 

__attribute__((used)) static int ixgbe_get_vf_reta(struct ixgbe_adapter *adapter, u32 *msgbuf, u32 vf)
{
	u32 i, j;
	u32 *out_buf = &msgbuf[1];
	const u8 *reta = adapter->rss_indir_tbl;
	u32 reta_size = ixgbe_rss_indir_tbl_entries(adapter);

	/* Check if operation is permitted */
	if (!adapter->vfinfo[vf].rss_query_enabled)
		return -EPERM;

	/* verify the PF is supporting the correct API */
	switch (adapter->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		break;
	default:
		return -EOPNOTSUPP;
	}

	/* This mailbox command is supported (required) only for 82599 and x540
	 * VFs which support up to 4 RSS queues. Therefore we will compress the
	 * RETA by saving only 2 bits from each entry. This way we will be able
	 * to transfer the whole RETA in a single mailbox operation.
	 */
	for (i = 0; i < reta_size / 16; i++) {
		out_buf[i] = 0;
		for (j = 0; j < 16; j++)
			out_buf[i] |= (u32)(reta[16 * i + j] & 0x3) << (2 * j);
	}

	return 0;
}