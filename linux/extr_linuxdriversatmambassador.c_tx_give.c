#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__* ptr; int /*<<< orphan*/  limit; int /*<<< orphan*/  start; } ;
struct TYPE_18__ {scalar_t__ pending; scalar_t__ maximum; scalar_t__ high; int /*<<< orphan*/  lock; int /*<<< orphan*/  filled; TYPE_2__ in; } ;
struct TYPE_17__ {int /*<<< orphan*/  flags; TYPE_4__ txq; } ;
typedef  TYPE_3__ tx_in ;
typedef  TYPE_4__ amb_txq ;
typedef  TYPE_3__ amb_dev ;
struct TYPE_15__ {int /*<<< orphan*/  tx_address; } ;
struct TYPE_14__ {TYPE_1__ adapter; } ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_TX ; 
 int EAGAIN ; 
 TYPE_3__* NEXTQ (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  TX_FRAME ; 
 int /*<<< orphan*/  amb_mem ; 
 int /*<<< orphan*/  dead ; 
 int /*<<< orphan*/  doorbell ; 
 TYPE_10__ mb ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_bus (TYPE_3__*) ; 
 int /*<<< orphan*/  wr_mem (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tx_give (amb_dev * dev, tx_in * tx) {
  amb_txq * txq = &dev->txq;
  unsigned long flags;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_give %p", dev);

  if (test_bit (dead, &dev->flags))
    return 0;
  
  spin_lock_irqsave (&txq->lock, flags);
  
  if (txq->pending < txq->maximum) {
    PRINTD (DBG_TX, "TX in slot %p", txq->in.ptr);

    *txq->in.ptr = *tx;
    txq->pending++;
    txq->in.ptr = NEXTQ (txq->in.ptr, txq->in.start, txq->in.limit);
    // hand over the TX and ring the bell
    wr_mem (dev, offsetof(amb_mem, mb.adapter.tx_address), virt_to_bus (txq->in.ptr));
    wr_mem (dev, offsetof(amb_mem, doorbell), TX_FRAME);
    
    if (txq->pending > txq->high)
      txq->high = txq->pending;
    spin_unlock_irqrestore (&txq->lock, flags);
    return 0;
  } else {
    txq->filled++;
    spin_unlock_irqrestore (&txq->lock, flags);
    return -EAGAIN;
  }
}