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
struct dma_desc {void* des3; void* des2; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwxgmac2_set_sec_addr(struct dma_desc *p, dma_addr_t addr)
{
	p->des2 = cpu_to_le32(lower_32_bits(addr));
	p->des3 = cpu_to_le32(upper_32_bits(addr));
}