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
typedef  int u8 ;
struct mlx5_ib_dev {TYPE_2__* mdev; int /*<<< orphan*/  ib_dev; } ;
struct ib_udata {int /*<<< orphan*/  outlen; int /*<<< orphan*/  inlen; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  max_pkeys; } ;
struct ib_device_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  max_pkeys; } ;
struct TYPE_4__ {TYPE_1__* port_caps; } ;
struct TYPE_3__ {int /*<<< orphan*/  gid_table_len; int /*<<< orphan*/  pkey_table_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ib_port_attr*) ; 
 struct ib_port_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_port_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_ib_query_device (int /*<<< orphan*/ *,struct ib_port_attr*,struct ib_udata*) ; 
 int mlx5_ib_query_port (int /*<<< orphan*/ *,int,struct ib_port_attr*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,...) ; 

__attribute__((used)) static int __get_port_caps(struct mlx5_ib_dev *dev, u8 port)
{
	struct ib_device_attr *dprops = NULL;
	struct ib_port_attr *pprops = NULL;
	int err = -ENOMEM;
	struct ib_udata uhw = {.inlen = 0, .outlen = 0};

	pprops = kzalloc(sizeof(*pprops), GFP_KERNEL);
	if (!pprops)
		goto out;

	dprops = kmalloc(sizeof(*dprops), GFP_KERNEL);
	if (!dprops)
		goto out;

	err = mlx5_ib_query_device(&dev->ib_dev, dprops, &uhw);
	if (err) {
		mlx5_ib_warn(dev, "query_device failed %d\n", err);
		goto out;
	}

	err = mlx5_ib_query_port(&dev->ib_dev, port, pprops);
	if (err) {
		mlx5_ib_warn(dev, "query_port %d failed %d\n",
			     port, err);
		goto out;
	}

	dev->mdev->port_caps[port - 1].pkey_table_len =
					dprops->max_pkeys;
	dev->mdev->port_caps[port - 1].gid_table_len =
					pprops->gid_tbl_len;
	mlx5_ib_dbg(dev, "port %d: pkey_table_len %d, gid_table_len %d\n",
		    port, dprops->max_pkeys, pprops->gid_tbl_len);

out:
	kfree(pprops);
	kfree(dprops);

	return err;
}