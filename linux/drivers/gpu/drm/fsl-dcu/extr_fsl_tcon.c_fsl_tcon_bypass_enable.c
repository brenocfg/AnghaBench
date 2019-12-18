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
struct fsl_tcon {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_TCON_CTRL1 ; 
 int /*<<< orphan*/  FSL_TCON_CTRL1_TCON_BYPASS ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fsl_tcon_bypass_enable(struct fsl_tcon *tcon)
{
	regmap_update_bits(tcon->regs, FSL_TCON_CTRL1,
			   FSL_TCON_CTRL1_TCON_BYPASS,
			   FSL_TCON_CTRL1_TCON_BYPASS);
}