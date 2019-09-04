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
struct ipu_soc {struct ipu_csi** csi_priv; } ;
struct ipu_csi {int inuse; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ipu_csi* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ipu_csi *ipu_csi_get(struct ipu_soc *ipu, int id)
{
	unsigned long flags;
	struct ipu_csi *csi, *ret;

	if (id > 1)
		return ERR_PTR(-EINVAL);

	csi = ipu->csi_priv[id];
	ret = csi;

	spin_lock_irqsave(&csi->lock, flags);

	if (csi->inuse) {
		ret = ERR_PTR(-EBUSY);
		goto unlock;
	}

	csi->inuse = true;
unlock:
	spin_unlock_irqrestore(&csi->lock, flags);
	return ret;
}