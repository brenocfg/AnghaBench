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
struct via_camera {scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static inline void viacam_write_reg(struct via_camera *cam,
		int reg, int value)
{
	iowrite32(value, cam->mmio + reg);
}