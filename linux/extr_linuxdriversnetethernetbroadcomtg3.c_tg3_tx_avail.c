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
typedef  scalar_t__ u32 ;
struct tg3_napi {int tx_prod; int tx_cons; scalar_t__ tx_pending; } ;

/* Variables and functions */
 int TG3_TX_RING_SIZE ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static inline u32 tg3_tx_avail(struct tg3_napi *tnapi)
{
	/* Tell compiler to fetch tx indices from memory. */
	barrier();
	return tnapi->tx_pending -
	       ((tnapi->tx_prod - tnapi->tx_cons) & (TG3_TX_RING_SIZE - 1));
}