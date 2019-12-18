#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  pa; int /*<<< orphan*/ * kva; } ;
struct bfa_port_s {TYPE_1__ stats_dma; } ;

/* Variables and functions */

void
bfa_port_mem_claim(struct bfa_port_s *port, u8 *dma_kva, u64 dma_pa)
{
	port->stats_dma.kva = dma_kva;
	port->stats_dma.pa  = dma_pa;
}