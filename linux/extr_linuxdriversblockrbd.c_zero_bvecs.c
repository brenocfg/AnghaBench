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
struct ceph_bvec_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bv ; 
 int /*<<< orphan*/  ceph_bvec_iter_advance (struct ceph_bvec_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_bvec_iter_advance_step (struct ceph_bvec_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_bvec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zero_bvecs(struct ceph_bvec_iter *bvec_pos, u32 off, u32 bytes)
{
	struct ceph_bvec_iter it = *bvec_pos;

	ceph_bvec_iter_advance(&it, off);
	ceph_bvec_iter_advance_step(&it, bytes, ({
		zero_bvec(&bv);
	}));
}