#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct c4iw_wr_wait {int dummy; } ;
struct TYPE_6__ {TYPE_2__* vr; } ;
struct c4iw_rdev {TYPE_3__ lldi; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {TYPE_1__ pbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int) ; 
 int write_adapter_mem (struct c4iw_rdev*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct c4iw_wr_wait*) ; 

__attribute__((used)) static int write_pbl(struct c4iw_rdev *rdev, __be64 *pbl,
		     u32 pbl_addr, u32 pbl_size, struct c4iw_wr_wait *wr_waitp)
{
	int err;

	pr_debug("*pdb_addr 0x%x, pbl_base 0x%x, pbl_size %d\n",
		 pbl_addr, rdev->lldi.vr->pbl.start,
		 pbl_size);

	err = write_adapter_mem(rdev, pbl_addr >> 5, pbl_size << 3, pbl, NULL,
				wr_waitp);
	return err;
}