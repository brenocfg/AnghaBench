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
struct ccp_device {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 struct ccp_device* ccp_rr ; 
 int /*<<< orphan*/  ccp_unit_lock ; 
 int /*<<< orphan*/  ccp_units ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ccp_add_device(struct ccp_device *ccp)
{
	unsigned long flags;

	write_lock_irqsave(&ccp_unit_lock, flags);
	list_add_tail(&ccp->entry, &ccp_units);
	if (!ccp_rr)
		/* We already have the list lock (we're first) so this
		 * pointer can't change on us. Set its initial value.
		 */
		ccp_rr = ccp;
	write_unlock_irqrestore(&ccp_unit_lock, flags);
}