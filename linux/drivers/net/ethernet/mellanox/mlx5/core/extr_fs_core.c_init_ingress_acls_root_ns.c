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
struct mlx5_flow_steering {int /*<<< orphan*/ * esw_ingress_root_ns; } ;
struct TYPE_2__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cleanup_root_ns (int /*<<< orphan*/ ) ; 
 int init_ingress_acl_root_ns (struct mlx5_flow_steering*,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mlx5_eswitch_get_total_vports (struct mlx5_core_dev*) ; 

__attribute__((used)) static int init_ingress_acls_root_ns(struct mlx5_core_dev *dev)
{
	struct mlx5_flow_steering *steering = dev->priv.steering;
	int total_vports = mlx5_eswitch_get_total_vports(dev);
	int err;
	int i;

	steering->esw_ingress_root_ns =
			kcalloc(total_vports,
				sizeof(*steering->esw_ingress_root_ns),
				GFP_KERNEL);
	if (!steering->esw_ingress_root_ns)
		return -ENOMEM;

	for (i = 0; i < total_vports; i++) {
		err = init_ingress_acl_root_ns(steering, i);
		if (err)
			goto cleanup_root_ns;
	}

	return 0;

cleanup_root_ns:
	for (i--; i >= 0; i--)
		cleanup_root_ns(steering->esw_ingress_root_ns[i]);
	kfree(steering->esw_ingress_root_ns);
	steering->esw_ingress_root_ns = NULL;
	return err;
}