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
struct TYPE_2__ {int num_tc; scalar_t__ pfc_en; } ;
struct hclge_dev {int /*<<< orphan*/  flag; TYPE_1__ tm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FLAG_DCB_ENABLE ; 
 int /*<<< orphan*/  hclge_pfc_info_init (struct hclge_dev*) ; 

void hclge_tm_pfc_info_update(struct hclge_dev *hdev)
{
	/* DCB is enabled if we have more than 1 TC or pfc_en is
	 * non-zero.
	 */
	if (hdev->tm_info.num_tc > 1 || hdev->tm_info.pfc_en)
		hdev->flag |= HCLGE_FLAG_DCB_ENABLE;
	else
		hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;

	hclge_pfc_info_init(hdev);
}