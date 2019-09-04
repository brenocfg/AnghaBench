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
union ib_gid {scalar_t__ raw; } ;
typedef  int u8 ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_smp {scalar_t__ data; void* attr_mod; int /*<<< orphan*/  attr_id; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_SMP_ATTR_GUID_INFO ; 
 int /*<<< orphan*/  IB_SMP_ATTR_PORT_INFO ; 
 int MLX4_MAD_IFC_IGNORE_KEYS ; 
 int MLX4_MAD_IFC_NET_VIEW ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int mlx4_MAD_IFC (struct mlx4_ib_dev*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 scalar_t__ mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

int __mlx4_ib_query_gid(struct ib_device *ibdev, u8 port, int index,
			union ib_gid *gid, int netw_view)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	int clear = 0;
	int mad_ifc_flags = MLX4_MAD_IFC_IGNORE_KEYS;

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	if (mlx4_is_mfunc(dev->dev) && netw_view)
		mad_ifc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(dev, mad_ifc_flags, port, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	memcpy(gid->raw, out_mad->data + 8, 8);

	if (mlx4_is_mfunc(dev->dev) && !netw_view) {
		if (index) {
			/* For any index > 0, return the null guid */
			err = 0;
			clear = 1;
			goto out;
		}
	}

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_GUID_INFO;
	in_mad->attr_mod = cpu_to_be32(index / 8);

	err = mlx4_MAD_IFC(dev, mad_ifc_flags, port,
			   NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	memcpy(gid->raw + 8, out_mad->data + (index % 8) * 8, 8);

out:
	if (clear)
		memset(gid->raw + 8, 0, 8);
	kfree(in_mad);
	kfree(out_mad);
	return err;
}