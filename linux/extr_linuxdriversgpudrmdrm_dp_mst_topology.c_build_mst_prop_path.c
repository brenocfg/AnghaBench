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
typedef  int /*<<< orphan*/  temp ;
struct drm_dp_mst_branch {int lct; int* rad; TYPE_1__* mgr; } ;
struct TYPE_2__ {int conn_base_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static void build_mst_prop_path(const struct drm_dp_mst_branch *mstb,
				int pnum,
				char *proppath,
				size_t proppath_size)
{
	int i;
	char temp[8];
	snprintf(proppath, proppath_size, "mst:%d", mstb->mgr->conn_base_id);
	for (i = 0; i < (mstb->lct - 1); i++) {
		int shift = (i % 2) ? 0 : 4;
		int port_num = (mstb->rad[i / 2] >> shift) & 0xf;
		snprintf(temp, sizeof(temp), "-%d", port_num);
		strlcat(proppath, temp, proppath_size);
	}
	snprintf(temp, sizeof(temp), "-%d", pnum);
	strlcat(proppath, temp, proppath_size);
}