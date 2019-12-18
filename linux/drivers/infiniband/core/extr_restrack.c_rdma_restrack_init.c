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
struct rdma_restrack_root {int /*<<< orphan*/  xa; } ;
struct ib_device {struct rdma_restrack_root* res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RDMA_RESTRACK_MAX ; 
 int /*<<< orphan*/  XA_FLAGS_ALLOC ; 
 struct rdma_restrack_root* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rdma_restrack_init(struct ib_device *dev)
{
	struct rdma_restrack_root *rt;
	int i;

	dev->res = kcalloc(RDMA_RESTRACK_MAX, sizeof(*rt), GFP_KERNEL);
	if (!dev->res)
		return -ENOMEM;

	rt = dev->res;

	for (i = 0; i < RDMA_RESTRACK_MAX; i++)
		xa_init_flags(&rt[i].xa, XA_FLAGS_ALLOC);

	return 0;
}