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
struct sky2_port {int tx_prod; int tx_cons; int tx_ring_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int tx_inuse(const struct sky2_port *sky2)
{
	return (sky2->tx_prod - sky2->tx_cons) & (sky2->tx_ring_size - 1);
}