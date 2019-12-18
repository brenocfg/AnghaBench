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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_PF (int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static u32 fsl_diu_get_pixel_format(unsigned int bits_per_pixel)
{
#define PF_BYTE_F		0x10000000
#define PF_ALPHA_C_MASK		0x0E000000
#define PF_ALPHA_C_SHIFT	25
#define PF_BLUE_C_MASK		0x01800000
#define PF_BLUE_C_SHIFT		23
#define PF_GREEN_C_MASK		0x00600000
#define PF_GREEN_C_SHIFT	21
#define PF_RED_C_MASK		0x00180000
#define PF_RED_C_SHIFT		19
#define PF_PALETTE		0x00040000
#define PF_PIXEL_S_MASK		0x00030000
#define PF_PIXEL_S_SHIFT	16
#define PF_COMP_3_MASK		0x0000F000
#define PF_COMP_3_SHIFT		12
#define PF_COMP_2_MASK		0x00000F00
#define PF_COMP_2_SHIFT		8
#define PF_COMP_1_MASK		0x000000F0
#define PF_COMP_1_SHIFT		4
#define PF_COMP_0_MASK		0x0000000F
#define PF_COMP_0_SHIFT		0

#define MAKE_PF(alpha, red, green, blue, size, c0, c1, c2, c3) \
	cpu_to_le32(PF_BYTE_F | (alpha << PF_ALPHA_C_SHIFT) | \
	(blue << PF_BLUE_C_SHIFT) | (green << PF_GREEN_C_SHIFT) | \
	(red << PF_RED_C_SHIFT) | (c3 << PF_COMP_3_SHIFT) | \
	(c2 << PF_COMP_2_SHIFT) | (c1 << PF_COMP_1_SHIFT) | \
	(c0 << PF_COMP_0_SHIFT) | (size << PF_PIXEL_S_SHIFT))

	switch (bits_per_pixel) {
	case 32:
		/* 0x88883316 */
		return MAKE_PF(3, 2, 1, 0, 3, 8, 8, 8, 8);
	case 24:
		/* 0x88082219 */
		return MAKE_PF(4, 0, 1, 2, 2, 8, 8, 8, 0);
	case 16:
		/* 0x65053118 */
		return MAKE_PF(4, 2, 1, 0, 1, 5, 6, 5, 0);
	default:
		pr_err("fsl-diu: unsupported color depth %u\n", bits_per_pixel);
		return 0;
	}
}