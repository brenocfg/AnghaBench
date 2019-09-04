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
struct pvrdma_dev {int dummy; } ;
struct ib_gid_attr {int /*<<< orphan*/  index; int /*<<< orphan*/  gid_type; int /*<<< orphan*/  gid; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_gid_type_to_pvrdma (int /*<<< orphan*/ ) ; 
 int pvrdma_add_gid_at_index (struct pvrdma_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvrdma_add_gid(const struct ib_gid_attr *attr, void **context)
{
	struct pvrdma_dev *dev = to_vdev(attr->device);

	return pvrdma_add_gid_at_index(dev, &attr->gid,
				       ib_gid_type_to_pvrdma(attr->gid_type),
				       attr->index);
}