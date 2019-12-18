#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mac {int /*<<< orphan*/  fec_mode; int /*<<< orphan*/  fec_ability; } ;
struct TYPE_2__ {struct hclge_mac mac; } ;
struct hclge_dev {TYPE_1__ hw; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_fec(struct hnae3_handle *handle, u8 *fec_ability,
			  u8 *fec_mode)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct hclge_mac *mac = &hdev->hw.mac;

	if (fec_ability)
		*fec_ability = mac->fec_ability;
	if (fec_mode)
		*fec_mode = mac->fec_mode;
}