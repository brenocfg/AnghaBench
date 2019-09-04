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
 unsigned int NR_MCAM_CLK ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcam_clk_enable(struct mcam_camera *mcam)
{
	unsigned int i;

	for (i = 0; i < NR_MCAM_CLK; i++) {
		if (!IS_ERR(mcam->clk[i]))
			clk_prepare_enable(mcam->clk[i]);
	}
}