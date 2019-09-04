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
 int /*<<< orphan*/  B ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  __FP_PACK_DS (void*,int /*<<< orphan*/ ) ; 

int
frsp(void *frD, void *frB)
{
	FP_DECL_D(B);
	FP_DECL_EX;

#ifdef DEBUG
	printk("%s: D %p, B %p\n", __func__, frD, frB);
#endif

	FP_UNPACK_DP(B, frB);

#ifdef DEBUG
	printk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	__FP_PACK_DS(frD, B);

	return FP_CUR_EXCEPTIONS;
}