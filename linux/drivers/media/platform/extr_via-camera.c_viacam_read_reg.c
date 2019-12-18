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
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static inline int viacam_read_reg(struct via_camera *cam, int reg)
{
	return ioread32(cam->mmio + reg);
}