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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_type {void* udp_ipv6; void* udp_ipv4; void* tcp_ipv6_ext; void* tcp_ipv6; void* tcp_ipv4; void* ipv6_ext; void* ipv6; void* ipv4; } ;
struct hinic_rss_context_table {int /*<<< orphan*/  context; scalar_t__ status; int /*<<< orphan*/  template_id; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  ctx_tbl ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_GET_RSS_CTX_TBL ; 
 void* HINIC_RSS_TYPE_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV4 ; 
 int /*<<< orphan*/  IPV6 ; 
 int /*<<< orphan*/  IPV6_EXT ; 
 int /*<<< orphan*/  TCP_IPV4 ; 
 int /*<<< orphan*/  TCP_IPV6 ; 
 int /*<<< orphan*/  TCP_IPV6_EXT ; 
 int /*<<< orphan*/  UDP_IPV4 ; 
 int /*<<< orphan*/  UDP_IPV6 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_context_table*,int,struct hinic_rss_context_table*,int*) ; 

int hinic_get_rss_type(struct hinic_dev *nic_dev, u32 tmpl_idx,
		       struct hinic_rss_type *rss_type)
{
	struct hinic_rss_context_table ctx_tbl = { 0 };
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u16 out_size = sizeof(ctx_tbl);
	int err;

	if (!hwdev || !rss_type)
		return -EINVAL;

	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	ctx_tbl.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	ctx_tbl.template_id = tmpl_idx;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_RSS_CTX_TBL,
				 &ctx_tbl, sizeof(ctx_tbl),
				 &ctx_tbl, &out_size);
	if (err || !out_size || ctx_tbl.status) {
		dev_err(&pdev->dev, "Failed to get hash type, err: %d, status: 0x%x, out size: 0x%x\n",
			err, ctx_tbl.status, out_size);
		return -EINVAL;
	}

	rss_type->ipv4          = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV4);
	rss_type->ipv6          = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV6);
	rss_type->ipv6_ext      = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV6_EXT);
	rss_type->tcp_ipv4      = HINIC_RSS_TYPE_GET(ctx_tbl.context, TCP_IPV4);
	rss_type->tcp_ipv6      = HINIC_RSS_TYPE_GET(ctx_tbl.context, TCP_IPV6);
	rss_type->tcp_ipv6_ext  = HINIC_RSS_TYPE_GET(ctx_tbl.context,
						     TCP_IPV6_EXT);
	rss_type->udp_ipv4      = HINIC_RSS_TYPE_GET(ctx_tbl.context, UDP_IPV4);
	rss_type->udp_ipv6      = HINIC_RSS_TYPE_GET(ctx_tbl.context, UDP_IPV6);

	return 0;
}