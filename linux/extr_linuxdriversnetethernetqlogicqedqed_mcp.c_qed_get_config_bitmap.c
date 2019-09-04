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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_QEDE ; 
 int CONFIG_QEDE_BITMAP_IDX ; 
 int CONFIG_QEDF_BITMAP_IDX ; 
 int CONFIG_QEDI_BITMAP_IDX ; 
 int CONFIG_QEDR_BITMAP_IDX ; 
 int /*<<< orphan*/  CONFIG_QED_FCOE ; 
 int /*<<< orphan*/  CONFIG_QED_ISCSI ; 
 int /*<<< orphan*/  CONFIG_QED_LL2 ; 
 int CONFIG_QED_LL2_BITMAP_IDX ; 
 int /*<<< orphan*/  CONFIG_QED_RDMA ; 
 int /*<<< orphan*/  CONFIG_QED_SRIOV ; 
 int CONFIG_QED_SRIOV_BITMAP_IDX ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qed_get_config_bitmap(void)
{
	u32 config_bitmap = 0x0;

	if (IS_ENABLED(CONFIG_QEDE))
		config_bitmap |= CONFIG_QEDE_BITMAP_IDX;

	if (IS_ENABLED(CONFIG_QED_SRIOV))
		config_bitmap |= CONFIG_QED_SRIOV_BITMAP_IDX;

	if (IS_ENABLED(CONFIG_QED_RDMA))
		config_bitmap |= CONFIG_QEDR_BITMAP_IDX;

	if (IS_ENABLED(CONFIG_QED_FCOE))
		config_bitmap |= CONFIG_QEDF_BITMAP_IDX;

	if (IS_ENABLED(CONFIG_QED_ISCSI))
		config_bitmap |= CONFIG_QEDI_BITMAP_IDX;

	if (IS_ENABLED(CONFIG_QED_LL2))
		config_bitmap |= CONFIG_QED_LL2_BITMAP_IDX;

	return config_bitmap;
}