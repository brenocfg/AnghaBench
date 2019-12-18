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
struct mthca_pd {int /*<<< orphan*/  pd_num; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {struct ib_device* device; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int mthca_pd_alloc (int /*<<< orphan*/ ,int,struct mthca_pd*) ; 
 int /*<<< orphan*/  mthca_pd_free (int /*<<< orphan*/ ,struct mthca_pd*) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 
 struct mthca_pd* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static int mthca_alloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct ib_device *ibdev = ibpd->device;
	struct mthca_pd *pd = to_mpd(ibpd);
	int err;

	err = mthca_pd_alloc(to_mdev(ibdev), !udata, pd);
	if (err)
		return err;

	if (udata) {
		if (ib_copy_to_udata(udata, &pd->pd_num, sizeof (__u32))) {
			mthca_pd_free(to_mdev(ibdev), pd);
			return -EFAULT;
		}
	}

	return 0;
}