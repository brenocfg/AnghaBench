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
struct qxl_device {int dummy; } ;

/* Variables and functions */

int qxl_ttm_debugfs_init(struct qxl_device *qdev)
{
#if defined(CONFIG_DEBUG_FS)
	static struct drm_info_list qxl_mem_types_list[QXL_DEBUGFS_MEM_TYPES];
	static char qxl_mem_types_names[QXL_DEBUGFS_MEM_TYPES][32];
	unsigned i;

	for (i = 0; i < QXL_DEBUGFS_MEM_TYPES; i++) {
		if (i == 0)
			sprintf(qxl_mem_types_names[i], "qxl_mem_mm");
		else
			sprintf(qxl_mem_types_names[i], "qxl_surf_mm");
		qxl_mem_types_list[i].name = qxl_mem_types_names[i];
		qxl_mem_types_list[i].show = &qxl_mm_dump_table;
		qxl_mem_types_list[i].driver_features = 0;
		if (i == 0)
			qxl_mem_types_list[i].data = qdev->mman.bdev.man[TTM_PL_VRAM].priv;
		else
			qxl_mem_types_list[i].data = qdev->mman.bdev.man[TTM_PL_PRIV].priv;

	}
	return qxl_debugfs_add_files(qdev, qxl_mem_types_list, i);
#else
	return 0;
#endif
}