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
typedef  scalar_t__ u32 ;
struct shmob_drm_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ LCDC_SIDE_B_OFFSET ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ lcdc_is_banked (scalar_t__) ; 

__attribute__((used)) static inline void lcdc_write(struct shmob_drm_device *sdev, u32 reg, u32 data)
{
	iowrite32(data, sdev->mmio + reg);
	if (lcdc_is_banked(reg))
		iowrite32(data, sdev->mmio + reg + LCDC_SIDE_B_OFFSET);
}