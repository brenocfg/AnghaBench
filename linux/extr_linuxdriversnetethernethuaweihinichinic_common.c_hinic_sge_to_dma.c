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
typedef  int u64 ;
struct hinic_sge {int lo_addr; scalar_t__ hi_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

dma_addr_t hinic_sge_to_dma(struct hinic_sge *sge)
{
	return (dma_addr_t)((((u64)sge->hi_addr) << 32) | sge->lo_addr);
}