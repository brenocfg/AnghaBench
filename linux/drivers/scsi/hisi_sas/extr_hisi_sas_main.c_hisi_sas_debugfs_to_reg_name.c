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
struct hisi_sas_debugfs_reg_lu {char const* name; int off; } ;

/* Variables and functions */

__attribute__((used)) static const char *
hisi_sas_debugfs_to_reg_name(int off, int base_off,
			     const struct hisi_sas_debugfs_reg_lu *lu)
{
	for (; lu->name; lu++) {
		if (off == lu->off - base_off)
			return lu->name;
	}

	return NULL;
}