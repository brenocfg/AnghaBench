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
struct c4iw_rdev {int /*<<< orphan*/  pbl_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_pblpool ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void c4iw_pblpool_destroy(struct c4iw_rdev *rdev)
{
	kref_put(&rdev->pbl_kref, destroy_pblpool);
}