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

/* Variables and functions */

void mlx5e_build_default_indir_rqt(u32 *indirection_rqt, int len,
				   int num_channels)
{
	int i;

	for (i = 0; i < len; i++)
		indirection_rqt[i] = i % num_channels;
}