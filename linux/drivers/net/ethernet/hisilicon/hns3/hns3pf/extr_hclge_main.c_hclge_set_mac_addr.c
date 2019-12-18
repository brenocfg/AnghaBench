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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_5__ {unsigned char const* mac_addr; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;
struct hclge_dev {TYPE_3__ hw; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ether_addr_copy (unsigned char const*,unsigned char const*) ; 
 int hclge_add_uc_addr (struct hnae3_handle*,unsigned char const*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_pause_addr_cfg (struct hclge_dev*,unsigned char const*) ; 
 scalar_t__ hclge_rm_uc_addr (struct hnae3_handle*,unsigned char const*) ; 
 scalar_t__ is_broadcast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_kdump_kernel () ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_zero_ether_addr (unsigned char const*) ; 

__attribute__((used)) static int hclge_set_mac_addr(struct hnae3_handle *handle, void *p,
			      bool is_first)
{
	const unsigned char *new_addr = (const unsigned char *)p;
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int ret;

	/* mac addr check */
	if (is_zero_ether_addr(new_addr) ||
	    is_broadcast_ether_addr(new_addr) ||
	    is_multicast_ether_addr(new_addr)) {
		dev_err(&hdev->pdev->dev,
			"Change uc mac err! invalid mac:%pM.\n",
			 new_addr);
		return -EINVAL;
	}

	if ((!is_first || is_kdump_kernel()) &&
	    hclge_rm_uc_addr(handle, hdev->hw.mac.mac_addr))
		dev_warn(&hdev->pdev->dev,
			 "remove old uc mac address fail.\n");

	ret = hclge_add_uc_addr(handle, new_addr);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"add uc mac address fail, ret =%d.\n",
			ret);

		if (!is_first &&
		    hclge_add_uc_addr(handle, hdev->hw.mac.mac_addr))
			dev_err(&hdev->pdev->dev,
				"restore uc mac address fail.\n");

		return -EIO;
	}

	ret = hclge_pause_addr_cfg(hdev, new_addr);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"configure mac pause address fail, ret =%d.\n",
			ret);
		return -EIO;
	}

	ether_addr_copy(hdev->hw.mac.mac_addr, new_addr);

	return 0;
}