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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct mlx5dr_ste_send_info {int /*<<< orphan*/  send_list; int /*<<< orphan*/ * data; int /*<<< orphan*/ * data_cont; void* offset; struct mlx5dr_ste* ste; void* size; } ;
struct mlx5dr_ste {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

void mlx5dr_send_fill_and_append_ste_send_info(struct mlx5dr_ste *ste, u16 size,
					       u16 offset, u8 *data,
					       struct mlx5dr_ste_send_info *ste_info,
					       struct list_head *send_list,
					       bool copy_data)
{
	ste_info->size = size;
	ste_info->ste = ste;
	ste_info->offset = offset;

	if (copy_data) {
		memcpy(ste_info->data_cont, data, size);
		ste_info->data = ste_info->data_cont;
	} else {
		ste_info->data = data;
	}

	list_add_tail(&ste_info->send_list, send_list);
}