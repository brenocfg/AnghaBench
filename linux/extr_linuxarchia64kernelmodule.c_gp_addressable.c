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
typedef  int uint64_t ;
struct TYPE_2__ {int gp; } ;
struct module {TYPE_1__ arch; } ;

/* Variables and functions */
 int MAX_LTOFF ; 

__attribute__((used)) static inline int
gp_addressable (struct module *mod, uint64_t value)
{
	return value - mod->arch.gp + MAX_LTOFF/2 < MAX_LTOFF;
}