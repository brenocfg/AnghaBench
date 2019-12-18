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
struct TYPE_3__ {unsigned long supported; unsigned long advertising; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclgevf_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static void hclgevf_get_link_mode(struct hnae3_handle *handle,
				  unsigned long *supported,
				  unsigned long *advertising)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	*supported = hdev->hw.mac.supported;
	*advertising = hdev->hw.mac.advertising;
}