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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct cxio_rdev {int dummy; } ;
typedef  enum tpt_mem_perm { ____Placeholder_tpt_mem_perm } tpt_mem_perm ;

/* Variables and functions */
 int /*<<< orphan*/  TPT_NON_SHARED_MR ; 
 int __cxio_tpt_op (struct cxio_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxio_reregister_phys_mem(struct cxio_rdev *rdev_p, u32 *stag, u32 pdid,
			   enum tpt_mem_perm perm, u32 zbva, u64 to, u32 len,
			   u8 page_size, u32 pbl_size, u32 pbl_addr)
{
	return __cxio_tpt_op(rdev_p, 0, stag, 1, pdid, TPT_NON_SHARED_MR, perm,
			     zbva, to, len, page_size, pbl_size, pbl_addr);
}