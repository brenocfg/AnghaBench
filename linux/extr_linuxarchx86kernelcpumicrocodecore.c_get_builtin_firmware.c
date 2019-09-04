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
struct cpio_data {int dummy; } ;

/* Variables and functions */

bool get_builtin_firmware(struct cpio_data *cd, const char *name)
{
#ifdef CONFIG_FW_LOADER
	struct builtin_fw *b_fw;

	for (b_fw = __start_builtin_fw; b_fw != __end_builtin_fw; b_fw++) {
		if (!strcmp(name, b_fw->name)) {
			cd->size = b_fw->size;
			cd->data = b_fw->data;
			return true;
		}
	}
#endif
	return false;
}