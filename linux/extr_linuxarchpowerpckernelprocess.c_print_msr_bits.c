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
 int /*<<< orphan*/  msr_bits ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  print_bits (unsigned long,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_tm_bits (unsigned long) ; 

__attribute__((used)) static void print_msr_bits(unsigned long val)
{
	pr_cont("<");
	print_bits(val, msr_bits, ",");
	print_tm_bits(val);
	pr_cont(">");
}