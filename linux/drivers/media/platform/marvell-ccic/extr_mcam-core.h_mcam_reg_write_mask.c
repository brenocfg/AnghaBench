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
struct mcam_camera {int dummy; } ;

/* Variables and functions */
 unsigned int mcam_reg_read (struct mcam_camera*,unsigned int) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void mcam_reg_write_mask(struct mcam_camera *cam, unsigned int reg,
		unsigned int val, unsigned int mask)
{
	unsigned int v = mcam_reg_read(cam, reg);

	v = (v & ~mask) | (val & mask);
	mcam_reg_write(cam, reg, v);
}