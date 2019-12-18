#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlx5dr_ste_htbl {TYPE_2__* chunk; } ;
struct mlx5dr_domain {TYPE_1__* send_ring; } ;
struct TYPE_4__ {int byte_size; int num_of_entries; } ;
struct TYPE_3__ {int max_post_send_size; } ;

/* Variables and functions */
 int DR_STE_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dr_get_tbl_copy_details(struct mlx5dr_domain *dmn,
				   struct mlx5dr_ste_htbl *htbl,
				   u8 **data,
				   u32 *byte_size,
				   int *iterations,
				   int *num_stes)
{
	int alloc_size;

	if (htbl->chunk->byte_size > dmn->send_ring->max_post_send_size) {
		*iterations = htbl->chunk->byte_size /
			dmn->send_ring->max_post_send_size;
		*byte_size = dmn->send_ring->max_post_send_size;
		alloc_size = *byte_size;
		*num_stes = *byte_size / DR_STE_SIZE;
	} else {
		*iterations = 1;
		*num_stes = htbl->chunk->num_of_entries;
		alloc_size = *num_stes * DR_STE_SIZE;
	}

	*data = kzalloc(alloc_size, GFP_KERNEL);
	if (!*data)
		return -ENOMEM;

	return 0;
}