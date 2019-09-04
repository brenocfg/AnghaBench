#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sun4i_ss_ctx {int /*<<< orphan*/  ssclk; int /*<<< orphan*/  busclk; scalar_t__ reset; scalar_t__ base; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rng; int /*<<< orphan*/  hash; int /*<<< orphan*/  crypto; } ;
struct TYPE_5__ {int type; TYPE_1__ alg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  CRYPTO_ALG_TYPE_AHASH 130 
#define  CRYPTO_ALG_TYPE_RNG 129 
#define  CRYPTO_ALG_TYPE_SKCIPHER 128 
 scalar_t__ SS_CTL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_rng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_skcipher (int /*<<< orphan*/ *) ; 
 struct sun4i_ss_ctx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 TYPE_2__* ss_algs ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun4i_ss_remove(struct platform_device *pdev)
{
	int i;
	struct sun4i_ss_ctx *ss = platform_get_drvdata(pdev);

	for (i = 0; i < ARRAY_SIZE(ss_algs); i++) {
		switch (ss_algs[i].type) {
		case CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unregister_skcipher(&ss_algs[i].alg.crypto);
			break;
		case CRYPTO_ALG_TYPE_AHASH:
			crypto_unregister_ahash(&ss_algs[i].alg.hash);
			break;
		case CRYPTO_ALG_TYPE_RNG:
			crypto_unregister_rng(&ss_algs[i].alg.rng);
			break;
		}
	}

	writel(0, ss->base + SS_CTL);
	if (ss->reset)
		reset_control_assert(ss->reset);
	clk_disable_unprepare(ss->busclk);
	clk_disable_unprepare(ss->ssclk);
	return 0;
}