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
struct xmitQel {int /*<<< orphan*/ * cbuf; struct xmitQel* next; } ;

/* Variables and functions */
 int DEBUG_LOWER ; 
 int debug ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  txqueue_lock ; 
 struct xmitQel* xmQhd ; 
 struct xmitQel* xmQtl ; 

__attribute__((used)) static void enQ(struct xmitQel *qel)
{
	unsigned long flags;
	qel->next = NULL;
	
	spin_lock_irqsave(&txqueue_lock, flags);
	if (xmQtl) {
		xmQtl->next = qel;
	} else {
		xmQhd = qel;
	}
	xmQtl = qel;
	spin_unlock_irqrestore(&txqueue_lock, flags);

	if (debug & DEBUG_LOWER)
		printk("enqueued a 0x%02x command\n",qel->cbuf[0]);
}