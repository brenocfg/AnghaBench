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
struct acm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_TTY_MINORS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acm_minors ; 
 int /*<<< orphan*/  acm_minors_lock ; 
 int idr_alloc (int /*<<< orphan*/ *,struct acm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acm_alloc_minor(struct acm *acm)
{
	int minor;

	mutex_lock(&acm_minors_lock);
	minor = idr_alloc(&acm_minors, acm, 0, ACM_TTY_MINORS, GFP_KERNEL);
	mutex_unlock(&acm_minors_lock);

	return minor;
}