#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {void* b; void* a; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int be64_to_cpu (void*) ; 
 void* cpu_to_be64 (int) ; 

__attribute__((used)) static void cmac_gf128_mul_by_x(be128 *y, const be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	y->a = cpu_to_be64((a << 1) | (b >> 63));
	y->b = cpu_to_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0));
}