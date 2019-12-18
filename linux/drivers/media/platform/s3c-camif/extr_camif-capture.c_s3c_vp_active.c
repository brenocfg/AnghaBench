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
struct camif_vp {int state; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int ST_VP_PENDING ; 
 int ST_VP_RUNNING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool s3c_vp_active(struct camif_vp *vp)
{
	struct camif_dev *camif = vp->camif;
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&camif->slock, flags);
	ret = (vp->state & ST_VP_RUNNING) || (vp->state & ST_VP_PENDING);
	spin_unlock_irqrestore(&camif->slock, flags);

	return ret;
}