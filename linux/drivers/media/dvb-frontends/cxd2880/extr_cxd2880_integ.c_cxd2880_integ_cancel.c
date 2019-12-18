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
struct cxd2880_tnrdmd {int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

int cxd2880_integ_cancel(struct cxd2880_tnrdmd *tnr_dmd)
{
	if (!tnr_dmd)
		return -EINVAL;

	atomic_set(&tnr_dmd->cancel, 1);

	return 0;
}