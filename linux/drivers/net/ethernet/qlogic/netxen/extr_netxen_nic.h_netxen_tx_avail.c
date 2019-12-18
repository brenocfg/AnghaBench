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
typedef  int /*<<< orphan*/  u32 ;
struct nx_host_tx_ring {int /*<<< orphan*/  num_desc; int /*<<< orphan*/  sw_consumer; int /*<<< orphan*/  producer; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_diff_among (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline u32 netxen_tx_avail(struct nx_host_tx_ring *tx_ring)
{
	smp_mb();
	return find_diff_among(tx_ring->producer,
			tx_ring->sw_consumer, tx_ring->num_desc);

}