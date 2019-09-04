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
struct mlx5_bfreg_info {struct mlx5_ib_ucontext* count; struct mlx5_ib_ucontext* sys_pages; } ;
struct mlx5_ib_ucontext {int /*<<< orphan*/  tdn; struct mlx5_bfreg_info bfregi; scalar_t__ devx_uid; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  deallocate_uars (struct mlx5_ib_dev*,struct mlx5_ib_ucontext*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_ucontext*) ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_transport_domain (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_devx_destroy (struct mlx5_ib_dev*,struct mlx5_ib_ucontext*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mlx5_ib_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct mlx5_ib_ucontext *context = to_mucontext(ibcontext);
	struct mlx5_ib_dev *dev = to_mdev(ibcontext->device);
	struct mlx5_bfreg_info *bfregi;

	if (context->devx_uid)
		mlx5_ib_devx_destroy(dev, context);

	bfregi = &context->bfregi;
	mlx5_ib_dealloc_transport_domain(dev, context->tdn);

	deallocate_uars(dev, context);
	kfree(bfregi->sys_pages);
	kfree(bfregi->count);
	kfree(context);

	return 0;
}