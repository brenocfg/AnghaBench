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
struct rhine_private {scalar_t__ cur_tx; scalar_t__ dirty_tx; } ;

/* Variables and functions */
 scalar_t__ TX_QUEUE_LEN ; 

__attribute__((used)) static inline bool rhine_tx_queue_full(struct rhine_private *rp)
{
	return (rp->cur_tx - rp->dirty_tx) >= TX_QUEUE_LEN;
}