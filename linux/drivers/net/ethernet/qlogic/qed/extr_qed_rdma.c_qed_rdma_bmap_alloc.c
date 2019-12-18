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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {int dummy; } ;
struct qed_bmap {int /*<<< orphan*/  name; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  max_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_MAX_BMAP_NAME ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

int qed_rdma_bmap_alloc(struct qed_hwfn *p_hwfn,
			struct qed_bmap *bmap, u32 max_count, char *name)
{
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "max_count = %08x\n", max_count);

	bmap->max_count = max_count;

	bmap->bitmap = kcalloc(BITS_TO_LONGS(max_count), sizeof(long),
			       GFP_KERNEL);
	if (!bmap->bitmap)
		return -ENOMEM;

	snprintf(bmap->name, QED_RDMA_MAX_BMAP_NAME, "%s", name);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "0\n");
	return 0;
}