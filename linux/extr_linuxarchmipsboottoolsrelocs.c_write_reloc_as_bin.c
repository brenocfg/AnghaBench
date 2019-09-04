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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_elf32 (int /*<<< orphan*/ ) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_reloc_as_bin(uint32_t v, FILE *f)
{
	unsigned char buf[4];

	v = cpu_to_elf32(v);

	memcpy(buf, &v, sizeof(uint32_t));
	return fwrite(buf, 1, 4, f);
}