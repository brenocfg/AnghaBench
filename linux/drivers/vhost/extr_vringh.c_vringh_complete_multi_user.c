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
struct vringh {int dummy; } ;
struct vring_used_elem {int dummy; } ;

/* Variables and functions */
 int __vringh_complete (struct vringh*,struct vring_used_elem const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putu16_user ; 
 int /*<<< orphan*/  putused_user ; 

int vringh_complete_multi_user(struct vringh *vrh,
			       const struct vring_used_elem used[],
			       unsigned num_used)
{
	return __vringh_complete(vrh, used, num_used,
				 putu16_user, putused_user);
}