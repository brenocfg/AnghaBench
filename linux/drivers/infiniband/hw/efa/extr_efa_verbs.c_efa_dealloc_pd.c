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
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct efa_pd {int /*<<< orphan*/  pdn; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  efa_pd_dealloc (struct efa_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 struct efa_pd* to_epd (struct ib_pd*) ; 

void efa_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibpd->device);
	struct efa_pd *pd = to_epd(ibpd);

	ibdev_dbg(&dev->ibdev, "Dealloc pd[%d]\n", pd->pdn);
	efa_pd_dealloc(dev, pd->pdn);
}