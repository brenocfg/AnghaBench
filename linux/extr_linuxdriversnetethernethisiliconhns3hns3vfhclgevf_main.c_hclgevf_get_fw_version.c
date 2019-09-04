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
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static u32 hclgevf_get_fw_version(struct hnae3_handle *handle)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	return hdev->fw_version;
}