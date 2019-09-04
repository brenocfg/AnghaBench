#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ base; } ;
struct module {TYPE_1__ init_layout; } ;

/* Variables and functions */

__attribute__((used)) static bool in_init(const struct module *mod, unsigned long loc)
{
	return loc - (u32)mod->init_layout.base < mod->init_layout.size;
}