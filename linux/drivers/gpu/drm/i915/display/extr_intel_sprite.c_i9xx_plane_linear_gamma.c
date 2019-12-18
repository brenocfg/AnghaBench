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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void i9xx_plane_linear_gamma(u16 gamma[8])
{
	/* The points are not evenly spaced. */
	static const u8 in[8] = { 0, 1, 2, 4, 8, 16, 24, 32 };
	int i;

	for (i = 0; i < 8; i++)
		gamma[i] = (in[i] << 8) / 32;
}