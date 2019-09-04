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

__attribute__((used)) static bool get_builtin_microcode(struct cpio_data *cp, unsigned int family)
{
#ifdef CONFIG_X86_64
	char fw_name[36] = "amd-ucode/microcode_amd.bin";

	if (family >= 0x15)
		snprintf(fw_name, sizeof(fw_name),
			 "amd-ucode/microcode_amd_fam%.2xh.bin", family);

	return get_builtin_firmware(cp, fw_name);
#else
	return false;
#endif
}