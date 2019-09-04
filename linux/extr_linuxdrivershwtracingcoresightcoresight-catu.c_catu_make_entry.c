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
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  cate_t ;

/* Variables and functions */
 int /*<<< orphan*/  CATU_VALID_ENTRY (scalar_t__) ; 

__attribute__((used)) static inline cate_t catu_make_entry(dma_addr_t addr)
{
	return addr ? CATU_VALID_ENTRY(addr) : 0;
}