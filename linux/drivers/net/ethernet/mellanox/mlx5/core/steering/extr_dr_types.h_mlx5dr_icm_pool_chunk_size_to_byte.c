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
typedef  enum mlx5dr_icm_type { ____Placeholder_mlx5dr_icm_type } mlx5dr_icm_type ;
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;

/* Variables and functions */
 int DR_ICM_TYPE_STE ; 
 int DR_MODIFY_ACTION_SIZE ; 
 int DR_STE_SIZE ; 
 int mlx5dr_icm_pool_chunk_size_to_entries (int) ; 

__attribute__((used)) static inline int
mlx5dr_icm_pool_chunk_size_to_byte(enum mlx5dr_icm_chunk_size chunk_size,
				   enum mlx5dr_icm_type icm_type)
{
	int num_of_entries;
	int entry_size;

	if (icm_type == DR_ICM_TYPE_STE)
		entry_size = DR_STE_SIZE;
	else
		entry_size = DR_MODIFY_ACTION_SIZE;

	num_of_entries = mlx5dr_icm_pool_chunk_size_to_entries(chunk_size);

	return entry_size * num_of_entries;
}