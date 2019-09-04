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
struct mtk_disp_mutex {int claimed; } ;
struct mtk_ddp {struct mtk_disp_mutex* mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct mtk_disp_mutex* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct mtk_ddp* dev_get_drvdata (struct device*) ; 

struct mtk_disp_mutex *mtk_disp_mutex_get(struct device *dev, unsigned int id)
{
	struct mtk_ddp *ddp = dev_get_drvdata(dev);

	if (id >= 10)
		return ERR_PTR(-EINVAL);
	if (ddp->mutex[id].claimed)
		return ERR_PTR(-EBUSY);

	ddp->mutex[id].claimed = true;

	return &ddp->mutex[id];
}