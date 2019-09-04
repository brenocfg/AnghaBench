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
struct ib_smp {scalar_t__ data; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_query_mad_ifc_smp_attr_node_info (struct ib_device*,struct ib_smp*) ; 

int mlx5_query_mad_ifc_max_pkeys(struct ib_device *ibdev,
				 u16 *max_pkeys)
{
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;

	out_mad = kmalloc(sizeof(*out_mad), GFP_KERNEL);
	if (!out_mad)
		return -ENOMEM;

	err = mlx5_query_mad_ifc_smp_attr_node_info(ibdev, out_mad);
	if (err)
		goto out;

	*max_pkeys = be16_to_cpup((__be16 *)(out_mad->data + 28));

out:
	kfree(out_mad);

	return err;
}