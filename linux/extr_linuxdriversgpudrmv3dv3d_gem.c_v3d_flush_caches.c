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
struct v3d_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v3d_invalidate_l1td (struct v3d_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_invalidate_l2t (struct v3d_dev*,int /*<<< orphan*/ ) ; 

void
v3d_flush_caches(struct v3d_dev *v3d)
{
	v3d_invalidate_l1td(v3d, 0);
	v3d_invalidate_l2t(v3d, 0);
}