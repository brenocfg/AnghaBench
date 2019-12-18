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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int u8 ;
struct mlx4_port_gid_table {TYPE_1__* gids; } ;
struct mlx4_ib_iboe {int /*<<< orphan*/  lock; struct mlx4_port_gid_table* gids; } ;
struct mlx4_ib_dev {struct mlx4_ib_iboe iboe; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;
struct TYPE_2__ {int gid_type; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  memcpy (union ib_gid*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rdma_is_zero_gid (union ib_gid*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fill_gid_by_hw_index(struct mlx4_ib_dev *ibdev, u8 port_num,
				int index, union ib_gid *gid,
				enum ib_gid_type *gid_type)
{
	struct mlx4_ib_iboe *iboe = &ibdev->iboe;
	struct mlx4_port_gid_table *port_gid_table;
	unsigned long flags;

	port_gid_table = &iboe->gids[port_num - 1];
	spin_lock_irqsave(&iboe->lock, flags);
	memcpy(gid, &port_gid_table->gids[index].gid, sizeof(*gid));
	*gid_type = port_gid_table->gids[index].gid_type;
	spin_unlock_irqrestore(&iboe->lock, flags);
	if (rdma_is_zero_gid(gid))
		return -ENOENT;

	return 0;
}