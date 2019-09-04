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
typedef  int /*<<< orphan*/  Elf32_Word ;

/* Variables and functions */
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Elf32_Word read_elf_word(Elf32_Word word, bool swap)
{
	return swap ? swab32(word) : word;
}