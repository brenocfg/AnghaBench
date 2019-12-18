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
struct omap3isp_hist_config {int num_regions; int /*<<< orphan*/  hist_bins; } ;

/* Variables and functions */
 int OMAP3ISP_HIST_MEM_SIZE_BINS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hist_get_buf_size(struct omap3isp_hist_config *conf)
{
	return OMAP3ISP_HIST_MEM_SIZE_BINS(conf->hist_bins) * conf->num_regions;
}