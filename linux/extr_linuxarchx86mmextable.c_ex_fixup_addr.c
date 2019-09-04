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
struct exception_table_entry {unsigned long fixup; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long
ex_fixup_addr(const struct exception_table_entry *x)
{
	return (unsigned long)&x->fixup + x->fixup;
}