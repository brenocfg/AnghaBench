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
struct TYPE_2__ {int bits; } ;
struct decode_header {TYPE_1__ type_regs; } ;

/* Variables and functions */
 int DECODE_TYPE_BITS ; 
 int* coverage_register_lookup ; 

unsigned coverage_start_registers(const struct decode_header *h)
{
	unsigned regs = 0;
	int i;
	for (i = 0; i < 20; i += 4) {
		int r = (h->type_regs.bits >> (DECODE_TYPE_BITS + i)) & 0xf;
		regs |= coverage_register_lookup[r] << i;
	}
	return regs;
}