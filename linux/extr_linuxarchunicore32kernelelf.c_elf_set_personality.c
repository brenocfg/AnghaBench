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
struct elf32_hdr {int dummy; } ;

/* Variables and functions */
 unsigned int PER_LINUX ; 
 int /*<<< orphan*/  set_personality (unsigned int) ; 

void elf_set_personality(const struct elf32_hdr *x)
{
	unsigned int personality = PER_LINUX;

	set_personality(personality);
}