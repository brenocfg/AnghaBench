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
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;

/* Variables and functions */
 int DR_CHUNK_SIZE_MAX ; 

__attribute__((used)) static inline enum mlx5dr_icm_chunk_size
mlx5dr_icm_next_higher_chunk(enum mlx5dr_icm_chunk_size chunk)
{
	chunk += 2;
	if (chunk < DR_CHUNK_SIZE_MAX)
		return chunk;

	return DR_CHUNK_SIZE_MAX;
}