#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pd_uinfo {int state; } ;
struct device {int dummy; } ;
struct crypto4xx_core_device {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  w; } ;
struct ce_pd {TYPE_1__ pd_ctl; } ;
struct TYPE_5__ {size_t pdr_tail; size_t pdr_head; struct ce_pd* pdr; struct pd_uinfo* pdr_uinfo; } ;

/* Variables and functions */
 int PD_CTL_HOST_READY ; 
 int PD_CTL_PE_DONE ; 
 int PD_ENTRY_INUSE ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_pd_done (TYPE_2__*,size_t) ; 
 size_t crypto4xx_put_pd_to_pdr (TYPE_2__*,size_t) ; 
 struct crypto4xx_core_device* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void crypto4xx_bh_tasklet_cb(unsigned long data)
{
	struct device *dev = (struct device *)data;
	struct crypto4xx_core_device *core_dev = dev_get_drvdata(dev);
	struct pd_uinfo *pd_uinfo;
	struct ce_pd *pd;
	u32 tail = core_dev->dev->pdr_tail;
	u32 head = core_dev->dev->pdr_head;

	do {
		pd_uinfo = &core_dev->dev->pdr_uinfo[tail];
		pd = &core_dev->dev->pdr[tail];
		if ((pd_uinfo->state & PD_ENTRY_INUSE) &&
		     ((READ_ONCE(pd->pd_ctl.w) &
		       (PD_CTL_PE_DONE | PD_CTL_HOST_READY)) ==
		       PD_CTL_PE_DONE)) {
			crypto4xx_pd_done(core_dev->dev, tail);
			tail = crypto4xx_put_pd_to_pdr(core_dev->dev, tail);
		} else {
			/* if tail not done, break */
			break;
		}
	} while (head != tail);
}