#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  start; TYPE_6__* ptr; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; TYPE_1__ out; scalar_t__ pending; } ;
typedef  TYPE_2__ amb_txq ;
struct TYPE_12__ {TYPE_2__ txq; } ;
typedef  TYPE_3__ amb_dev ;
struct TYPE_13__ {scalar_t__ handle; } ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_TX ; 
 TYPE_6__* NEXTQ (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_complete (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static int tx_take (amb_dev * dev) {
  amb_txq * txq = &dev->txq;
  unsigned long flags;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_take %p", dev);
  
  spin_lock_irqsave (&txq->lock, flags);
  
  if (txq->pending && txq->out.ptr->handle) {
    // deal with TX completion
    tx_complete (dev, txq->out.ptr);
    // mark unused again
    txq->out.ptr->handle = 0;
    // remove item
    txq->pending--;
    txq->out.ptr = NEXTQ (txq->out.ptr, txq->out.start, txq->out.limit);
    
    spin_unlock_irqrestore (&txq->lock, flags);
    return 0;
  } else {
    
    spin_unlock_irqrestore (&txq->lock, flags);
    return -1;
  }
}