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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 short BLACK ; 
 int DIFFUSING_MATRIX_HEIGHT ; 
 int DIFFUSING_MATRIX_WIDTH ; 
 short WHITE ; 
 char** diffusing_matrix ; 

__attribute__((used)) static void iterate_diffusion_matrix(u32 xres, u32 yres, int x,
				     int y, signed short *convert_buf,
				     signed short pixel, signed short error)
{
	u16 i, j;

	/* diffusion matrix row */
	for (i = 0; i < DIFFUSING_MATRIX_WIDTH; ++i)
		/* diffusion matrix column */
		for (j = 0; j < DIFFUSING_MATRIX_HEIGHT; ++j) {
			signed short *write_pos;
			signed char coeff;

			/* skip pixels out of zone */
			if (x + i < 0 || x + i >= xres || y + j >= yres)
				continue;
			write_pos = &convert_buf[(y + j) * xres + x + i];
			coeff = diffusing_matrix[i][j];
			if (-1 == coeff) {
				/* pixel itself */
				*write_pos = pixel;
			} else {
				signed short p = *write_pos + error * coeff;

				if (p > WHITE)
					p = WHITE;
				if (p < BLACK)
					p = BLACK;
				*write_pos = p;
			}
		}
}