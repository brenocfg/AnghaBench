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
typedef  scalar_t__ u64 ;
struct ioremap_mem_flags {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ioremap_res_check ; 
 int /*<<< orphan*/  memset (struct ioremap_mem_flags*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walk_mem_res (scalar_t__,scalar_t__,struct ioremap_mem_flags*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ioremap_check_mem(resource_size_t addr, unsigned long size,
				struct ioremap_mem_flags *flags)
{
	u64 start, end;

	start = (u64)addr;
	end = start + size - 1;
	memset(flags, 0, sizeof(*flags));

	walk_mem_res(start, end, flags, __ioremap_res_check);
}