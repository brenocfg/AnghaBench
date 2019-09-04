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
struct s3c24xx_dma_phy {int /*<<< orphan*/ * serving; int /*<<< orphan*/  clk; struct s3c24xx_dma_engine* host; } ;
struct s3c24xx_dma_engine {TYPE_1__* sdata; } ;
struct TYPE_2__ {scalar_t__ has_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s3c24xx_dma_put_phy(struct s3c24xx_dma_phy *phy)
{
	struct s3c24xx_dma_engine *s3cdma = phy->host;

	if (s3cdma->sdata->has_clocks)
		clk_disable(phy->clk);

	phy->serving = NULL;
}