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
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int dummy; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_config_gro (struct hclgevf_dev*,int) ; 

__attribute__((used)) static int hclgevf_gro_en(struct hnae3_handle *handle, bool enable)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	return hclgevf_config_gro(hdev, enable);
}