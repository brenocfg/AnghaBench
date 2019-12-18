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
struct hclgevf_dev {int dummy; } ;

/* Variables and functions */
 int hclgevf_cmd_set_promisc_mode (struct hclgevf_dev*,int) ; 

__attribute__((used)) static int hclgevf_set_promisc_mode(struct hclgevf_dev *hdev, bool en_bc_pmc)
{
	return hclgevf_cmd_set_promisc_mode(hdev, en_bc_pmc);
}