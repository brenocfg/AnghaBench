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
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int UBI_LAYOUT_VOLUME_COMPAT ; 
 int UBI_LAYOUT_VOLUME_ID ; 

__attribute__((used)) static int ubi_get_compat(const struct ubi_device *ubi, int vol_id)
{
	if (vol_id == UBI_LAYOUT_VOLUME_ID)
		return UBI_LAYOUT_VOLUME_COMPAT;
	return 0;
}