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
typedef  int uint32_t ;

/* Variables and functions */
 int R200_VTX_DISCRETE_FOG ; 
 int R200_VTX_N0 ; 
 int R200_VTX_N1 ; 
 int R200_VTX_POINT_SIZE ; 
 int R200_VTX_PV_MATRIX_SEL ; 
 int R200_VTX_SHININESS_0 ; 
 int R200_VTX_SHININESS_1 ; 
 int R200_VTX_W0 ; 
 int R200_VTX_W1 ; 
 int R200_VTX_WEIGHT_COUNT_SHIFT ; 
 int R200_VTX_XY1 ; 
 int R200_VTX_Z0 ; 
 int R200_VTX_Z1 ; 

__attribute__((used)) static int r200_get_vtx_size_0(uint32_t vtx_fmt_0)
{
	int vtx_size, i;
	vtx_size = 2;

	if (vtx_fmt_0 & R200_VTX_Z0)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_W0)
		vtx_size++;
	/* blend weight */
	if (vtx_fmt_0 & (0x7 << R200_VTX_WEIGHT_COUNT_SHIFT))
		vtx_size += (vtx_fmt_0 >> R200_VTX_WEIGHT_COUNT_SHIFT) & 0x7;
	if (vtx_fmt_0 & R200_VTX_PV_MATRIX_SEL)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_N0)
		vtx_size += 3;
	if (vtx_fmt_0 & R200_VTX_POINT_SIZE)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_DISCRETE_FOG)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_SHININESS_0)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_SHININESS_1)
		vtx_size++;
	for (i = 0; i < 8; i++) {
		int color_size = (vtx_fmt_0 >> (11 + 2*i)) & 0x3;
		switch (color_size) {
		case 0: break;
		case 1: vtx_size++; break;
		case 2: vtx_size += 3; break;
		case 3: vtx_size += 4; break;
		}
	}
	if (vtx_fmt_0 & R200_VTX_XY1)
		vtx_size += 2;
	if (vtx_fmt_0 & R200_VTX_Z1)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_W1)
		vtx_size++;
	if (vtx_fmt_0 & R200_VTX_N1)
		vtx_size += 3;
	return vtx_size;
}