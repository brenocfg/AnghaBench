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
struct t4_sq {int dummy; } ;
struct c4iw_rdev {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int alloc_host_sq (struct c4iw_rdev*,struct t4_sq*) ; 
 int alloc_oc_sq (struct c4iw_rdev*,struct t4_sq*) ; 

__attribute__((used)) static int alloc_sq(struct c4iw_rdev *rdev, struct t4_sq *sq, int user)
{
	int ret = -ENOSYS;
	if (user)
		ret = alloc_oc_sq(rdev, sq);
	if (ret)
		ret = alloc_host_sq(rdev, sq);
	return ret;
}