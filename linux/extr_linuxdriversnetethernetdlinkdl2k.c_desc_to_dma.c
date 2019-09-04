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
struct netdev_desc {int /*<<< orphan*/  fraginfo; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t desc_to_dma(struct netdev_desc *desc)
{
	return le64_to_cpu(desc->fraginfo) & DMA_BIT_MASK(48);
}