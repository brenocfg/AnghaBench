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
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  read_spr (int,unsigned long*) ; 

__attribute__((used)) static void dump_one_spr(int spr, bool show_unimplemented)
{
	unsigned long val;

	val = 0xdeadbeef;
	if (!read_spr(spr, &val)) {
		printf("SPR 0x%03x (%4d) Faulted during read\n", spr, spr);
		return;
	}

	if (val == 0xdeadbeef) {
		/* Looks like read was a nop, confirm */
		val = 0x0badcafe;
		if (!read_spr(spr, &val)) {
			printf("SPR 0x%03x (%4d) Faulted during read\n", spr, spr);
			return;
		}

		if (val == 0x0badcafe) {
			if (show_unimplemented)
				printf("SPR 0x%03x (%4d) Unimplemented\n", spr, spr);
			return;
		}
	}

	printf("SPR 0x%03x (%4d) = 0x%lx\n", spr, spr, val);
}