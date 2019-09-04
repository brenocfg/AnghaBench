#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rx_in ;
struct TYPE_10__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  limit; int /*<<< orphan*/  start; } ;
struct TYPE_11__ {scalar_t__ pending; scalar_t__ maximum; int /*<<< orphan*/  lock; TYPE_2__ in; } ;
typedef  TYPE_3__ amb_rxq ;
struct TYPE_12__ {TYPE_3__* rxq; } ;
typedef  TYPE_4__ amb_dev ;
struct TYPE_9__ {int /*<<< orphan*/ * rx_address; } ;
struct TYPE_13__ {TYPE_1__ adapter; } ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_RX ; 
 int /*<<< orphan*/ * NEXTQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_4__*,...) ; 
 int /*<<< orphan*/  amb_mem ; 
 TYPE_7__ mb ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_mem (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx_give (amb_dev * dev, rx_in * rx, unsigned char pool) {
  amb_rxq * rxq = &dev->rxq[pool];
  unsigned long flags;
  
  PRINTD (DBG_FLOW|DBG_RX, "rx_give %p[%hu]", dev, pool);
  
  spin_lock_irqsave (&rxq->lock, flags);
  
  if (rxq->pending < rxq->maximum) {
    PRINTD (DBG_RX, "RX in slot %p", rxq->in.ptr);

    *rxq->in.ptr = *rx;
    rxq->pending++;
    rxq->in.ptr = NEXTQ (rxq->in.ptr, rxq->in.start, rxq->in.limit);
    // hand over the RX buffer
    wr_mem (dev, offsetof(amb_mem, mb.adapter.rx_address[pool]), virt_to_bus (rxq->in.ptr));
    
    spin_unlock_irqrestore (&rxq->lock, flags);
    return 0;
  } else {
    spin_unlock_irqrestore (&rxq->lock, flags);
    return -1;
  }
}