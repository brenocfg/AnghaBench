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
struct machine_desc {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  early_print (char*) ; 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static inline const struct machine_desc *
setup_machine_tags(phys_addr_t __atags_pointer, unsigned int machine_nr)
{
	early_print("no ATAGS support: can't continue\n");
	while (true);
	unreachable();
}