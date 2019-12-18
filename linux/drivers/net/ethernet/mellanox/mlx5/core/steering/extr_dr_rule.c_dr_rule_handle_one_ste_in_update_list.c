#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_ste_send_info {int /*<<< orphan*/  data; TYPE_1__* ste; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  send_list; } ;
struct mlx5dr_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_ste; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE_REDUCED ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_ste_send_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5dr_send_postsend_ste (struct mlx5dr_domain*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dr_rule_handle_one_ste_in_update_list(struct mlx5dr_ste_send_info *ste_info,
				      struct mlx5dr_domain *dmn)
{
	int ret;

	list_del(&ste_info->send_list);
	ret = mlx5dr_send_postsend_ste(dmn, ste_info->ste, ste_info->data,
				       ste_info->size, ste_info->offset);
	if (ret)
		goto out;
	/* Copy data to ste, only reduced size, the last 16B (mask)
	 * is already written to the hw.
	 */
	memcpy(ste_info->ste->hw_ste, ste_info->data, DR_STE_SIZE_REDUCED);

out:
	kfree(ste_info);
	return ret;
}