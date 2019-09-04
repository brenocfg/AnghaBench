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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 struct hfi1_devdata* __hfi1_lookup (int) ; 
 int /*<<< orphan*/  hfi1_devs_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct hfi1_devdata *hfi1_lookup(int unit)
{
	struct hfi1_devdata *dd;
	unsigned long flags;

	spin_lock_irqsave(&hfi1_devs_lock, flags);
	dd = __hfi1_lookup(unit);
	spin_unlock_irqrestore(&hfi1_devs_lock, flags);

	return dd;
}