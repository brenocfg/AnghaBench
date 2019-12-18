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
struct etnaviv_cmdbuf {scalar_t__ suballoc_offset; TYPE_1__* suballoc; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ paddr; } ;

/* Variables and functions */

dma_addr_t etnaviv_cmdbuf_get_pa(struct etnaviv_cmdbuf *buf)
{
	return buf->suballoc->paddr + buf->suballoc_offset;
}