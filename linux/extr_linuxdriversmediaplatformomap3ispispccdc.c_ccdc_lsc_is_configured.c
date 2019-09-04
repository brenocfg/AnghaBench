#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  req_lock; int /*<<< orphan*/ * active; } ;
struct isp_ccdc_device {TYPE_1__ lsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int ccdc_lsc_is_configured(struct isp_ccdc_device *ccdc)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	ret = ccdc->lsc.active != NULL;
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);

	return ret;
}