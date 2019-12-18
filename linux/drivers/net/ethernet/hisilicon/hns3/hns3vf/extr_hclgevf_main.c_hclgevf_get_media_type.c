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
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_handle {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  module_type; int /*<<< orphan*/  media_type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclgevf_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static void hclgevf_get_media_type(struct hnae3_handle *handle, u8 *media_type,
				   u8 *module_type)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	if (media_type)
		*media_type = hdev->hw.mac.media_type;

	if (module_type)
		*module_type = hdev->hw.mac.module_type;
}