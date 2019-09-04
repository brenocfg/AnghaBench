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
struct TYPE_2__ {int* m32; } ;
struct fp_ext {TYPE_1__ mant; } ;

/* Variables and functions */

__attribute__((used)) static inline int fp_overnormalize(struct fp_ext *reg)
{
	int shift;

	if (reg->mant.m32[0]) {
		asm ("bfffo %1{#0,#32},%0" : "=d" (shift) : "dm" (reg->mant.m32[0]));
		reg->mant.m32[0] = (reg->mant.m32[0] << shift) | (reg->mant.m32[1] >> (32 - shift));
		reg->mant.m32[1] = (reg->mant.m32[1] << shift);
	} else {
		asm ("bfffo %1{#0,#32},%0" : "=d" (shift) : "dm" (reg->mant.m32[1]));
		reg->mant.m32[0] = (reg->mant.m32[1] << shift);
		reg->mant.m32[1] = 0;
		shift += 32;
	}

	return shift;
}