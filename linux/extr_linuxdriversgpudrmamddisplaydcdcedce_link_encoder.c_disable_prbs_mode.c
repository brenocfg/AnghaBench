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
struct dce110_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_PRBS_EN ; 
 int /*<<< orphan*/  DP_DPHY_PRBS_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_prbs_mode(
	struct dce110_link_encoder *enc110)
{
	REG_UPDATE(DP_DPHY_PRBS_CNTL, DPHY_PRBS_EN, 0);
}