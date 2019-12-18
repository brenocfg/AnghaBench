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
struct TYPE_2__ {int /*<<< orphan*/  core; } ;
struct bgmac {TYPE_1__ bcma; } ;

/* Variables and functions */
 int bcma_core_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bcma_bgmac_clk_enabled(struct bgmac *bgmac)
{
	return bcma_core_is_enabled(bgmac->bcma.core);
}