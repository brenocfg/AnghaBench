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

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,size_t) ; 
 int /*<<< orphan*/  sram_pool ; 

void sram_free(void *addr, size_t len)
{
	gen_pool_free(sram_pool, (unsigned long) addr, len);
}