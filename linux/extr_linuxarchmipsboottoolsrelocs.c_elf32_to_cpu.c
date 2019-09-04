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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__* e_ident; } ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__ ehdr ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t elf32_to_cpu(uint32_t val)
{
	if (ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		return le32_to_cpu(val);
	else
		return be32_to_cpu(val);
}