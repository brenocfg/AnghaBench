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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ccp_unit_lock ; 
 int /*<<< orphan*/  ccp_units ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ccp_present(void)
{
	unsigned long flags;
	int ret;

	read_lock_irqsave(&ccp_unit_lock, flags);
	ret = list_empty(&ccp_units);
	read_unlock_irqrestore(&ccp_unit_lock, flags);

	return ret ? -ENODEV : 0;
}