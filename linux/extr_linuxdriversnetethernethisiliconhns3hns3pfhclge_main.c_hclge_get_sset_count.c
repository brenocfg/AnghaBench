#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hnae3_handle {int flags; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {scalar_t__ speed; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ETH_SS_STATS ; 
 int ETH_SS_TEST ; 
 scalar_t__ HCLGE_MAC_SPEED_100M ; 
 scalar_t__ HCLGE_MAC_SPEED_10M ; 
 scalar_t__ HCLGE_MAC_SPEED_1G ; 
 int HNAE3_SUPPORT_MAC_LOOPBACK ; 
 int HNAE3_SUPPORT_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  g_all_32bit_stats_string ; 
 int /*<<< orphan*/  g_all_64bit_stats_string ; 
 int /*<<< orphan*/  g_mac_stats_string ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_tqps_get_sset_count (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hclge_get_sset_count(struct hnae3_handle *handle, int stringset)
{
#define HCLGE_LOOPBACK_TEST_FLAGS 0x7

	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int count = 0;

	/* Loopback test support rules:
	 * mac: only GE mode support
	 * serdes: all mac mode will support include GE/XGE/LGE/CGE
	 * phy: only support when phy device exist on board
	 */
	if (stringset == ETH_SS_TEST) {
		/* clear loopback bit flags at first */
		handle->flags = (handle->flags & (~HCLGE_LOOPBACK_TEST_FLAGS));
		if (hdev->hw.mac.speed == HCLGE_MAC_SPEED_10M ||
		    hdev->hw.mac.speed == HCLGE_MAC_SPEED_100M ||
		    hdev->hw.mac.speed == HCLGE_MAC_SPEED_1G) {
			count += 1;
			handle->flags |= HNAE3_SUPPORT_MAC_LOOPBACK;
		}

		count++;
		handle->flags |= HNAE3_SUPPORT_SERDES_LOOPBACK;
	} else if (stringset == ETH_SS_STATS) {
		count = ARRAY_SIZE(g_mac_stats_string) +
			ARRAY_SIZE(g_all_32bit_stats_string) +
			ARRAY_SIZE(g_all_64bit_stats_string) +
			hclge_tqps_get_sset_count(handle, stringset);
	}

	return count;
}