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
typedef  int /*<<< orphan*/  u8 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SBC_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_SUBS_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_SUB_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_a32_sub_r(const u8 dst, const u8 src,
				  const bool is64, const bool hi,
				  struct jit_ctx *ctx) {
	/* 64 bit :
	 *	subs dst_lo, dst_lo, src_lo
	 *	sbc dst_hi, dst_hi, src_hi
	 * 32 bit :
	 *	sub dst_lo, dst_lo, src_lo
	 */
	if (!hi && is64)
		emit(ARM_SUBS_R(dst, dst, src), ctx);
	else if (hi && is64)
		emit(ARM_SBC_R(dst, dst, src), ctx);
	else
		emit(ARM_SUB_R(dst, dst, src), ctx);
}