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
typedef  int u8 ;
struct malidp_hw_device {TYPE_2__* hw; } ;
struct TYPE_3__ {int bus_align_bytes; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 malidp_hw_get_pitch_align(struct malidp_hw_device *hwdev, bool rotated)
{
	/*
	 * only hardware that cannot do 8 bytes bus alignments have further
	 * constraints on rotated planes
	 */
	if (hwdev->hw->map.bus_align_bytes == 8)
		return 8;
	else
		return hwdev->hw->map.bus_align_bytes << (rotated ? 2 : 0);
}