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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int alloc_tqps; struct hclge_dev* back; } ;
struct TYPE_3__ {scalar_t__ link; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_cfg_mac_mode (struct hclge_dev*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_mac_start_phy (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_tqp_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_tqp_enable (struct hclge_dev*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int hclge_ae_start(struct hnae3_handle *handle)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int i;

	for (i = 0; i < vport->alloc_tqps; i++)
		hclge_tqp_enable(hdev, i, 0, true);

	/* mac enable */
	hclge_cfg_mac_mode(hdev, true);
	clear_bit(HCLGE_STATE_DOWN, &hdev->state);
	mod_timer(&hdev->service_timer, jiffies + HZ);
	hdev->hw.mac.link = 0;

	/* reset tqp stats */
	hclge_reset_tqp_stats(handle);

	hclge_mac_start_phy(hdev);

	return 0;
}