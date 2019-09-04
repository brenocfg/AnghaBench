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
struct hypfs_diag0c_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X00C ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diag0c(struct hypfs_diag0c_entry *entry)
{
	diag_stat_inc(DIAG_STAT_X00C);
	asm volatile (
		"	sam31\n"
		"	diag	%0,%0,0x0c\n"
		"	sam64\n"
		: /* no output register */
		: "a" (entry)
		: "memory");
}