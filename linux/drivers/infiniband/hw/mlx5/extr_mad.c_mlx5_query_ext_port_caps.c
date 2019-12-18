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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct ib_smp {int /*<<< orphan*/  status; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; } ;
struct TYPE_4__ {TYPE_1__* port_caps; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext_port_cap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_ATTR_EXTENDED_PORT_INFO ; 
 int /*<<< orphan*/  MLX_EXT_PORT_CAP_FLAG_EXTENDED_PORT_INFO ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_MAD_IFC (struct mlx5_ib_dev*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 

int mlx5_query_ext_port_caps(struct mlx5_ib_dev *dev, u8 port)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;
	u16 packet_error;

	in_mad  = kzalloc(sizeof(*in_mad), GFP_KERNEL);
	out_mad = kmalloc(sizeof(*out_mad), GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id = MLX5_ATTR_EXTENDED_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mlx5_MAD_IFC(dev, 1, 1, 1, NULL, NULL, in_mad, out_mad);

	packet_error = be16_to_cpu(out_mad->status);

	dev->mdev->port_caps[port - 1].ext_port_cap = (!err && !packet_error) ?
		MLX_EXT_PORT_CAP_FLAG_EXTENDED_PORT_INFO : 0;

out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}