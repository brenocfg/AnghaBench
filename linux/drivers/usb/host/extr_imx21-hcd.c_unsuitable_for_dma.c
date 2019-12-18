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
typedef  int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline bool unsuitable_for_dma(dma_addr_t addr)
{
	return (addr & 3) != 0;
}