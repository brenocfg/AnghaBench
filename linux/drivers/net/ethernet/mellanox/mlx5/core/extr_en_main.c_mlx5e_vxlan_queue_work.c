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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_vxlan_work {int /*<<< orphan*/  work; int /*<<< orphan*/  port; struct mlx5e_priv* priv; } ;
struct mlx5e_priv {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5e_vxlan_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_vxlan_add_work ; 
 int /*<<< orphan*/  mlx5e_vxlan_del_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_vxlan_queue_work(struct mlx5e_priv *priv, u16 port, int add)
{
	struct mlx5e_vxlan_work *vxlan_work;

	vxlan_work = kmalloc(sizeof(*vxlan_work), GFP_ATOMIC);
	if (!vxlan_work)
		return;

	if (add)
		INIT_WORK(&vxlan_work->work, mlx5e_vxlan_add_work);
	else
		INIT_WORK(&vxlan_work->work, mlx5e_vxlan_del_work);

	vxlan_work->priv = priv;
	vxlan_work->port = port;
	queue_work(priv->wq, &vxlan_work->work);
}