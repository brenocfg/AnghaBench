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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_rng_dev {int datum_size; scalar_t__ csr_base; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  READY_MASK ; 
 scalar_t__ RNG_INOUT_0 ; 
 scalar_t__ RNG_INTR_STS_ACK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xgene_rng_data_read(struct hwrng *rng, u32 *data)
{
	struct xgene_rng_dev *ctx = (struct xgene_rng_dev *) rng->priv;
	int i;

	for (i = 0; i < ctx->datum_size; i++)
		data[i] = readl(ctx->csr_base + RNG_INOUT_0 + i * 4);

	/* Clear ready bit to start next transaction */
	writel(READY_MASK, ctx->csr_base + RNG_INTR_STS_ACK);

	return ctx->datum_size << 2;
}