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
struct ocxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCXL_NUM_MINORS ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ocxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minors_idr ; 
 int /*<<< orphan*/  minors_idr_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allocate_afu_minor(struct ocxl_afu *afu)
{
	int minor;

	mutex_lock(&minors_idr_lock);
	minor = idr_alloc(&minors_idr, afu, 0, OCXL_NUM_MINORS, GFP_KERNEL);
	mutex_unlock(&minors_idr_lock);
	return minor;
}