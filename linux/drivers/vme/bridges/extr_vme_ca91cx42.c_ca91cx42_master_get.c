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
struct vme_master_resource {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __ca91cx42_master_get (struct vme_master_resource*,int*,unsigned long long*,unsigned long long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ca91cx42_master_get(struct vme_master_resource *image, int *enabled,
	unsigned long long *vme_base, unsigned long long *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
{
	int retval;

	spin_lock(&image->lock);

	retval = __ca91cx42_master_get(image, enabled, vme_base, size, aspace,
		cycle, dwidth);

	spin_unlock(&image->lock);

	return retval;
}