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
struct rvt_pd {int dummy; } ;
struct rvt_dev_info {int /*<<< orphan*/  n_pds_lock; int /*<<< orphan*/  n_pds_allocated; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_pd* ibpd_to_rvtpd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct rvt_pd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int rvt_dealloc_pd(struct ib_pd *ibpd)
{
	struct rvt_pd *pd = ibpd_to_rvtpd(ibpd);
	struct rvt_dev_info *dev = ib_to_rvt(ibpd->device);

	spin_lock(&dev->n_pds_lock);
	dev->n_pds_allocated--;
	spin_unlock(&dev->n_pds_lock);

	kfree(pd);

	return 0;
}