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
struct seq_file {int dummy; } ;
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_AUDIO_CFG ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_CFG2 ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_CTRL ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_DATA ; 
 int /*<<< orphan*/  HDMI_WP_CLK ; 
 int /*<<< orphan*/  HDMI_WP_DEBOUNCE ; 
 int /*<<< orphan*/  HDMI_WP_IRQENABLE_CLR ; 
 int /*<<< orphan*/  HDMI_WP_IRQENABLE_SET ; 
 int /*<<< orphan*/  HDMI_WP_IRQSTATUS ; 
 int /*<<< orphan*/  HDMI_WP_IRQSTATUS_RAW ; 
 int /*<<< orphan*/  HDMI_WP_IRQWAKEEN ; 
 int /*<<< orphan*/  HDMI_WP_PWR_CTRL ; 
 int /*<<< orphan*/  HDMI_WP_REVISION ; 
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_CFG ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_SIZE ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_TIMING_H ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_TIMING_V ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

void hdmi_wp_dump(struct hdmi_wp_data *wp, struct seq_file *s)
{
#define DUMPREG(r) seq_printf(s, "%-35s %08x\n", #r, hdmi_read_reg(wp->base, r))

	DUMPREG(HDMI_WP_REVISION);
	DUMPREG(HDMI_WP_SYSCONFIG);
	DUMPREG(HDMI_WP_IRQSTATUS_RAW);
	DUMPREG(HDMI_WP_IRQSTATUS);
	DUMPREG(HDMI_WP_IRQENABLE_SET);
	DUMPREG(HDMI_WP_IRQENABLE_CLR);
	DUMPREG(HDMI_WP_IRQWAKEEN);
	DUMPREG(HDMI_WP_PWR_CTRL);
	DUMPREG(HDMI_WP_DEBOUNCE);
	DUMPREG(HDMI_WP_VIDEO_CFG);
	DUMPREG(HDMI_WP_VIDEO_SIZE);
	DUMPREG(HDMI_WP_VIDEO_TIMING_H);
	DUMPREG(HDMI_WP_VIDEO_TIMING_V);
	DUMPREG(HDMI_WP_CLK);
	DUMPREG(HDMI_WP_AUDIO_CFG);
	DUMPREG(HDMI_WP_AUDIO_CFG2);
	DUMPREG(HDMI_WP_AUDIO_CTRL);
	DUMPREG(HDMI_WP_AUDIO_DATA);
}