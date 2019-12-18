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
struct ufs_hba {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_ref_clk_freq; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_CLK_FREQ_INVAL ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  ufs_get_bref_clk_from_hz (unsigned long) ; 

void ufshcd_parse_dev_ref_clk_freq(struct ufs_hba *hba, struct clk *refclk)
{
	unsigned long freq;

	freq = clk_get_rate(refclk);

	hba->dev_ref_clk_freq =
		ufs_get_bref_clk_from_hz(freq);

	if (hba->dev_ref_clk_freq == REF_CLK_FREQ_INVAL)
		dev_err(hba->dev,
		"invalid ref_clk setting = %ld\n", freq);
}