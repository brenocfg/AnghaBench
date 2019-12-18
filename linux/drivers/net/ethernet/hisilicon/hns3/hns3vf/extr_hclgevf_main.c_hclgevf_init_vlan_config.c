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
struct hclgevf_dev {int /*<<< orphan*/  nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int hclgevf_set_vlan_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_init_vlan_config(struct hclgevf_dev *hdev)
{
	return hclgevf_set_vlan_filter(&hdev->nic, htons(ETH_P_8021Q), 0,
				       false);
}