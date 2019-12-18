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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_type {int ipv4; int ipv6; int ipv6_ext; int tcp_ipv4; int tcp_ipv6; int tcp_ipv6_ext; int udp_ipv4; int udp_ipv6; } ;
struct hinic_rss_context_tbl {int size; void* ctx; scalar_t__ rsvd; scalar_t__ offset; void* group_index; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_func_to_io {int /*<<< orphan*/  cmdqs; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; struct hinic_func_to_io func_to_io; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
struct hinic_cmdq_buf {int size; scalar_t__ buf; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HINIC_MOD_L2NIC ; 
 int HINIC_RSS_TYPE_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_UCODE_CMD_SET_RSS_CONTEXT_TABLE ; 
 int /*<<< orphan*/  IPV4 ; 
 int /*<<< orphan*/  IPV6 ; 
 int /*<<< orphan*/  IPV6_EXT ; 
 int /*<<< orphan*/  TCP_IPV4 ; 
 int /*<<< orphan*/  TCP_IPV6 ; 
 int /*<<< orphan*/  TCP_IPV6_EXT ; 
 int /*<<< orphan*/  UDP_IPV4 ; 
 int /*<<< orphan*/  UDP_IPV6 ; 
 int /*<<< orphan*/  VALID ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hinic_alloc_cmdq_buf (int /*<<< orphan*/ *,struct hinic_cmdq_buf*) ; 
 int hinic_cmdq_direct_resp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hinic_cmdq_buf*,scalar_t__*) ; 
 int /*<<< orphan*/  hinic_free_cmdq_buf (int /*<<< orphan*/ *,struct hinic_cmdq_buf*) ; 

int hinic_set_rss_type(struct hinic_dev *nic_dev, u32 tmpl_idx,
		       struct hinic_rss_type rss_type)
{
	struct hinic_rss_context_tbl *ctx_tbl;
	struct hinic_func_to_io *func_to_io;
	struct hinic_cmdq_buf cmd_buf;
	struct hinic_hwdev *hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u64 out_param;
	u32 ctx = 0;
	int err;

	hwdev = nic_dev->hwdev;
	func_to_io = &hwdev->func_to_io;
	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate cmd buf\n");
		return -ENOMEM;
	}

	ctx |=  HINIC_RSS_TYPE_SET(1, VALID) |
		HINIC_RSS_TYPE_SET(rss_type.ipv4, IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.ipv6, IPV6) |
		HINIC_RSS_TYPE_SET(rss_type.ipv6_ext, IPV6_EXT) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv4, TCP_IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv6, TCP_IPV6) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv6_ext, TCP_IPV6_EXT) |
		HINIC_RSS_TYPE_SET(rss_type.udp_ipv4, UDP_IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.udp_ipv6, UDP_IPV6);

	cmd_buf.size = sizeof(struct hinic_rss_context_tbl);

	ctx_tbl = (struct hinic_rss_context_tbl *)cmd_buf.buf;
	ctx_tbl->group_index = cpu_to_be32(tmpl_idx);
	ctx_tbl->offset = 0;
	ctx_tbl->size = sizeof(u32);
	ctx_tbl->size = cpu_to_be32(ctx_tbl->size);
	ctx_tbl->rsvd = 0;
	ctx_tbl->ctx = cpu_to_be32(ctx);

	/* cfg the rss context table by command queue */
	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_CONTEXT_TABLE,
				     &cmd_buf, &out_param);

	hinic_free_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);

	if (err || out_param != 0) {
		dev_err(&pdev->dev, "Failed to set rss context table, err: %d\n",
			err);
		return -EFAULT;
	}

	return 0;
}