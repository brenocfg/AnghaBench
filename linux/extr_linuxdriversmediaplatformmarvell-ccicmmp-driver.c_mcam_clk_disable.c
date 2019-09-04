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
struct mcam_camera {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int NR_MCAM_CLK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcam_clk_disable(struct mcam_camera *mcam)
{
	int i;

	for (i = NR_MCAM_CLK - 1; i >= 0; i--) {
		if (!IS_ERR(mcam->clk[i]))
			clk_disable_unprepare(mcam->clk[i]);
	}
}