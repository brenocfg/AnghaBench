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
struct qed_rdma_device {scalar_t__ reserved_lkey; } ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {struct qed_rdma_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 scalar_t__ RDMA_RESERVED_LKEY ; 
 int /*<<< orphan*/  qed_rdma_alloc_tid (struct qed_hwfn*,scalar_t__*) ; 

__attribute__((used)) static int qed_rdma_reserve_lkey(struct qed_hwfn *p_hwfn)
{
	struct qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	/* Tid 0 will be used as the key for "reserved MR".
	 * The driver should allocate memory for it so it can be loaded but no
	 * ramrod should be passed on it.
	 */
	qed_rdma_alloc_tid(p_hwfn, &dev->reserved_lkey);
	if (dev->reserved_lkey != RDMA_RESERVED_LKEY) {
		DP_NOTICE(p_hwfn,
			  "Reserved lkey should be equal to RDMA_RESERVED_LKEY\n");
		return -EINVAL;
	}

	return 0;
}