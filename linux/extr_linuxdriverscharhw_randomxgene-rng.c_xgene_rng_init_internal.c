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
typedef  int u32 ;
struct xgene_rng_dev {scalar_t__ csr_base; } ;

/* Variables and functions */
 int ALARM_THRESHOLD_SET (int /*<<< orphan*/ ,int) ; 
 int ENABLE_RNG_SET (int /*<<< orphan*/ ,int) ; 
 int LONG_RUN_FAIL_MASK ; 
 int LONG_RUN_FAIL_MASK_SET (int,int) ; 
 int MAX_REFILL_CYCLES_SET (int /*<<< orphan*/ ,int) ; 
 int MIN_REFILL_CYCLES_SET (int,int) ; 
 int MONOBIT_FAIL_MASK ; 
 int MONOBIT_FAIL_MASK_SET (int,int) ; 
 int NOISE_FAIL_MASK ; 
 int NOISE_FAIL_MASK_SET (int,int) ; 
 int POKER_FAIL_MASK ; 
 int POKER_FAIL_MASK_SET (int,int) ; 
 int READY_MASK ; 
 scalar_t__ RNG_ALARMCNT ; 
 scalar_t__ RNG_CONFIG ; 
 scalar_t__ RNG_CONTROL ; 
 scalar_t__ RNG_INTR_STS_ACK ; 
 int RUN_FAIL_MASK ; 
 int RUN_FAIL_MASK_SET (int,int) ; 
 int SHUTDOWN_OFLO_MASK ; 
 int SHUTDOWN_OFLO_MASK_SET (int,int) ; 
 int STUCK_OUT_MASK ; 
 int STUCK_OUT_MASK_SET (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xgene_rng_init_fro (struct xgene_rng_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_rng_init_internal(struct xgene_rng_dev *ctx)
{
	u32 val;

	writel(0x00000000, ctx->csr_base + RNG_CONTROL);

	val = MAX_REFILL_CYCLES_SET(0, 10);
	val = MIN_REFILL_CYCLES_SET(val, 10);
	writel(val, ctx->csr_base + RNG_CONFIG);

	val = ALARM_THRESHOLD_SET(0, 0xFF);
	writel(val, ctx->csr_base + RNG_ALARMCNT);

	xgene_rng_init_fro(ctx, 0);

	writel(MONOBIT_FAIL_MASK |
		POKER_FAIL_MASK	|
		LONG_RUN_FAIL_MASK |
		RUN_FAIL_MASK |
		NOISE_FAIL_MASK |
		STUCK_OUT_MASK |
		SHUTDOWN_OFLO_MASK |
		READY_MASK, ctx->csr_base + RNG_INTR_STS_ACK);

	val = ENABLE_RNG_SET(0, 1);
	val = MONOBIT_FAIL_MASK_SET(val, 1);
	val = POKER_FAIL_MASK_SET(val, 1);
	val = LONG_RUN_FAIL_MASK_SET(val, 1);
	val = RUN_FAIL_MASK_SET(val, 1);
	val = NOISE_FAIL_MASK_SET(val, 1);
	val = STUCK_OUT_MASK_SET(val, 1);
	val = SHUTDOWN_OFLO_MASK_SET(val, 1);
	writel(val, ctx->csr_base + RNG_CONTROL);
}