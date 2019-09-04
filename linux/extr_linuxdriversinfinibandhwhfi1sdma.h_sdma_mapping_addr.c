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
struct sdma_desc {int* qw; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int SDMA_DESC0_PHY_ADDR_SHIFT ; 
 int SDMA_DESC0_PHY_ADDR_SMASK ; 

__attribute__((used)) static inline dma_addr_t sdma_mapping_addr(struct sdma_desc *d)
{
	return (d->qw[0] & SDMA_DESC0_PHY_ADDR_SMASK)
		>> SDMA_DESC0_PHY_ADDR_SHIFT;
}