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

/* Variables and functions */
#define  UBI_LAYOUT_VOLUME_ID 128 

__attribute__((used)) static bool vol_ignored(int vol_id)
{
	switch (vol_id) {
		case UBI_LAYOUT_VOLUME_ID:
		return true;
	}

#ifdef CONFIG_MTD_UBI_FASTMAP
	return ubi_is_fm_vol(vol_id);
#else
	return false;
#endif
}