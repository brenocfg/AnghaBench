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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CAAM_CMD_SZ ; 
 int CAAM_PTR_SZ ; 
 scalar_t__ caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_caam32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_caam_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ desc_end (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline void append_ptr(u32 * const desc, dma_addr_t ptr)
{
	dma_addr_t *offset = (dma_addr_t *)desc_end(desc);

	*offset = cpu_to_caam_dma(ptr);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				CAAM_PTR_SZ / CAAM_CMD_SZ);
}