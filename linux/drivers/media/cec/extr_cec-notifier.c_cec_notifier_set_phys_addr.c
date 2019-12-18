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
typedef  int /*<<< orphan*/  u16 ;
struct cec_notifier {int /*<<< orphan*/  lock; int /*<<< orphan*/  phys_addr; scalar_t__ cec_adap; int /*<<< orphan*/  (* callback ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cec_s_phys_addr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

void cec_notifier_set_phys_addr(struct cec_notifier *n, u16 pa)
{
	if (n == NULL)
		return;

	mutex_lock(&n->lock);
	n->phys_addr = pa;
	if (n->callback)
		n->callback(n->cec_adap, n->phys_addr);
	else if (n->cec_adap)
		cec_s_phys_addr(n->cec_adap, n->phys_addr, false);
	mutex_unlock(&n->lock);
}