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
struct mlx4_func_cap {int /*<<< orphan*/  phys_port_id; int /*<<< orphan*/  spec_qps; } ;
struct mlx4_caps {int num_ports; int /*<<< orphan*/ * pkey_table_len; int /*<<< orphan*/ * gid_table_len; int /*<<< orphan*/ * phys_port_id; int /*<<< orphan*/ * port_type; int /*<<< orphan*/ * port_mask; int /*<<< orphan*/ * spec_qps; } ;
struct mlx4_dev {struct mlx4_caps caps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_func_cap*) ; 
 struct mlx4_func_cap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_QUERY_FUNC_CAP (struct mlx4_dev*,int,struct mlx4_func_cap*) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int mlx4_get_slave_pkey_gid_tbl_len (struct mlx4_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_slave_destroy_special_qp_cap (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_slave_special_qp_cap(struct mlx4_dev *dev)
{
	struct mlx4_func_cap *func_cap = NULL;
	struct mlx4_caps *caps = &dev->caps;
	int i, err = 0;

	func_cap = kzalloc(sizeof(*func_cap), GFP_KERNEL);
	caps->spec_qps = kcalloc(caps->num_ports, sizeof(*caps->spec_qps), GFP_KERNEL);

	if (!func_cap || !caps->spec_qps) {
		mlx4_err(dev, "Failed to allocate memory for special qps cap\n");
		err = -ENOMEM;
		goto err_mem;
	}

	for (i = 1; i <= caps->num_ports; ++i) {
		err = mlx4_QUERY_FUNC_CAP(dev, i, func_cap);
		if (err) {
			mlx4_err(dev, "QUERY_FUNC_CAP port command failed for port %d, aborting (%d)\n",
				 i, err);
			goto err_mem;
		}
		caps->spec_qps[i - 1] = func_cap->spec_qps;
		caps->port_mask[i] = caps->port_type[i];
		caps->phys_port_id[i] = func_cap->phys_port_id;
		err = mlx4_get_slave_pkey_gid_tbl_len(dev, i,
						      &caps->gid_table_len[i],
						      &caps->pkey_table_len[i]);
		if (err) {
			mlx4_err(dev, "QUERY_PORT command failed for port %d, aborting (%d)\n",
				 i, err);
			goto err_mem;
		}
	}

err_mem:
	if (err)
		mlx4_slave_destroy_special_qp_cap(dev);
	kfree(func_cap);
	return err;
}