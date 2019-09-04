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
struct mlx5_ib_dev {int dummy; } ;
struct ib_smp {int /*<<< orphan*/  data; int /*<<< orphan*/  attr_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_DEVICE_NODE_DESC_MAX ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_DESC ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_MAD_IFC (struct mlx5_ib_dev*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 

int mlx5_query_mad_ifc_node_desc(struct mlx5_ib_dev *dev, char *node_desc)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;

	in_mad  = kzalloc(sizeof(*in_mad), GFP_KERNEL);
	out_mad = kmalloc(sizeof(*out_mad), GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_DESC;

	err = mlx5_MAD_IFC(dev, 1, 1, 1, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	memcpy(node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);
out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}