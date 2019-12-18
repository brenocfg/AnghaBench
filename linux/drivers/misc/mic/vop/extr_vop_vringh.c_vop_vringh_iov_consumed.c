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
typedef  int /*<<< orphan*/  u32 ;
struct vringh_kiov {int i; TYPE_1__* iov; int /*<<< orphan*/  consumed; } ;
struct TYPE_2__ {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 vop_vringh_iov_consumed(struct vringh_kiov *iov)
{
	int i;
	u32 total = iov->consumed;

	for (i = 0; i < iov->i; i++)
		total += iov->iov[i].iov_len;
	return total;
}