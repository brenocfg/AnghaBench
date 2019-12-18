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
struct TYPE_2__ {int /*<<< orphan*/  node_guid; int /*<<< orphan*/ * node_desc; } ;
struct mthca_dev {TYPE_1__ ib_dev; int /*<<< orphan*/  rev_id; } ;
struct ib_smp {scalar_t__ data; int /*<<< orphan*/  attr_id; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_DEVICE_NODE_DESC_MAX ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_DESC ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_INFO ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int mthca_MAD_IFC (struct mthca_dev*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

__attribute__((used)) static int mthca_init_node_data(struct mthca_dev *dev)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_DESC;

	err = mthca_MAD_IFC(dev, 1, 1,
			    1, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	memcpy(dev->ib_dev.node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);

	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mthca_MAD_IFC(dev, 1, 1,
			    1, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	if (mthca_is_memfree(dev))
		dev->rev_id = be32_to_cpup((__be32 *) (out_mad->data + 32));
	memcpy(&dev->ib_dev.node_guid, out_mad->data + 12, 8);

out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}