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
struct resource {int dummy; } ;
struct ioremap_mem_flags {scalar_t__ desc_other; scalar_t__ system_ram; } ;

/* Variables and functions */
 scalar_t__ __ioremap_check_desc_other (struct resource*) ; 
 scalar_t__ __ioremap_check_ram (struct resource*) ; 

__attribute__((used)) static int __ioremap_res_check(struct resource *res, void *arg)
{
	struct ioremap_mem_flags *flags = arg;

	if (!flags->system_ram)
		flags->system_ram = __ioremap_check_ram(res);

	if (!flags->desc_other)
		flags->desc_other = __ioremap_check_desc_other(res);

	return flags->system_ram && flags->desc_other;
}