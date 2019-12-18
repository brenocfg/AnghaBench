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
struct ib_smp {int /*<<< orphan*/  attr_id; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_INFO ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_MAD_IFC (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 

int mlx5_query_mad_ifc_smp_attr_node_info(struct ib_device *ibdev,
					  struct ib_smp *out_mad)
{
	struct ib_smp *in_mad = NULL;
	int err = -ENOMEM;

	in_mad = kzalloc(sizeof(*in_mad), GFP_KERNEL);
	if (!in_mad)
		return -ENOMEM;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx5_MAD_IFC(to_mdev(ibdev), 1, 1, 1, NULL, NULL, in_mad,
			   out_mad);

	kfree(in_mad);
	return err;
}