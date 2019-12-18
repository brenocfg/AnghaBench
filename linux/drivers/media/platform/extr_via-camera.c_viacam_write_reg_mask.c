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
struct via_camera {int dummy; } ;

/* Variables and functions */
 int viacam_read_reg (struct via_camera*,int) ; 
 int /*<<< orphan*/  viacam_write_reg (struct via_camera*,int,int) ; 

__attribute__((used)) static inline void viacam_write_reg_mask(struct via_camera *cam,
		int reg, int value, int mask)
{
	int tmp = viacam_read_reg(cam, reg);

	tmp = (tmp & ~mask) | (value & mask);
	viacam_write_reg(cam, reg, tmp);
}