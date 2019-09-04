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
struct ib_smp {scalar_t__ data; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int mlx5_query_mad_ifc_smp_attr_node_info (struct ib_device*,struct ib_smp*) ; 

int mlx5_query_mad_ifc_system_image_guid(struct ib_device *ibdev,
					 __be64 *sys_image_guid)
{
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;

	out_mad = kmalloc(sizeof(*out_mad), GFP_KERNEL);
	if (!out_mad)
		return -ENOMEM;

	err = mlx5_query_mad_ifc_smp_attr_node_info(ibdev, out_mad);
	if (err)
		goto out;

	memcpy(sys_image_guid, out_mad->data + 4, 8);

out:
	kfree(out_mad);

	return err;
}