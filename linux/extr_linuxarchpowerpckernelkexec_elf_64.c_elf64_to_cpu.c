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
typedef  int /*<<< orphan*/  uint64_t ;
struct elfhdr {scalar_t__* e_ident; } ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFDATA2MSB ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t elf64_to_cpu(const struct elfhdr *ehdr, uint64_t value)
{
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		value = le64_to_cpu(value);
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		value = be64_to_cpu(value);

	return value;
}