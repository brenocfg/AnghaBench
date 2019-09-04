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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_WRITE_COMBINE ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pgprot_t __get_dma_pgprot(unsigned long attrs, pgprot_t prot,
				 bool coherent)
{
	if (!coherent || (attrs & DMA_ATTR_WRITE_COMBINE))
		return pgprot_writecombine(prot);
	return prot;
}