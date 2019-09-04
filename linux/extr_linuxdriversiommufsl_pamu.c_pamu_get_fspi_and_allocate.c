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
typedef  int u32 ;
struct paace {int dummy; } ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spaace_pool ; 
 scalar_t__ spaact ; 

__attribute__((used)) static unsigned long pamu_get_fspi_and_allocate(u32 subwin_cnt)
{
	unsigned long spaace_addr;

	spaace_addr = gen_pool_alloc(spaace_pool, subwin_cnt * sizeof(struct paace));
	if (!spaace_addr)
		return ULONG_MAX;

	return (spaace_addr - (unsigned long)spaact) / (sizeof(struct paace));
}