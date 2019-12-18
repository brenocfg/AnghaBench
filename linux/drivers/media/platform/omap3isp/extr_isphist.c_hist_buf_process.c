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
struct omap3isp_hist_config {scalar_t__ num_acc_frames; } ;
struct ispstat {scalar_t__ state; scalar_t__ wait_acc_frames; scalar_t__ dma_ch; int /*<<< orphan*/  buf_err; struct omap3isp_hist_config* priv; } ;

/* Variables and functions */
 scalar_t__ ISPSTAT_ENABLED ; 
 int STAT_NO_BUF ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int hist_buf_dma (struct ispstat*) ; 
 int hist_buf_pio (struct ispstat*) ; 
 int /*<<< orphan*/  hist_reset_mem (struct ispstat*) ; 

__attribute__((used)) static int hist_buf_process(struct ispstat *hist)
{
	struct omap3isp_hist_config *user_cfg = hist->priv;
	int ret;

	if (atomic_read(&hist->buf_err) || hist->state != ISPSTAT_ENABLED) {
		hist_reset_mem(hist);
		return STAT_NO_BUF;
	}

	if (--(hist->wait_acc_frames))
		return STAT_NO_BUF;

	if (hist->dma_ch)
		ret = hist_buf_dma(hist);
	else
		ret = hist_buf_pio(hist);

	hist->wait_acc_frames = user_cfg->num_acc_frames;

	return ret;
}