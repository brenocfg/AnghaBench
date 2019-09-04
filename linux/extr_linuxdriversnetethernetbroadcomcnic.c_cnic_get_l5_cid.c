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
typedef  size_t u32 ;
struct cnic_local {size_t max_cid_space; TYPE_1__* ctx_tbl; } ;
struct TYPE_2__ {size_t cid; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cnic_get_l5_cid(struct cnic_local *cp, u32 cid, u32 *l5_cid)
{
	u32 i;

	if (!cp->ctx_tbl)
		return -EINVAL;

	for (i = 0; i < cp->max_cid_space; i++) {
		if (cp->ctx_tbl[i].cid == cid) {
			*l5_cid = i;
			return 0;
		}
	}
	return -EINVAL;
}