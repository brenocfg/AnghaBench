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
struct mtk_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTS_CTRL_SOFT ; 
 int /*<<< orphan*/  GRL_CTS_CTRL ; 
 int /*<<< orphan*/  mtk_hdmi_mask (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_ncts_enable(struct mtk_hdmi *hdmi, bool on)
{
	mtk_hdmi_mask(hdmi, GRL_CTS_CTRL, on ? 0 : CTS_CTRL_SOFT,
		      CTS_CTRL_SOFT);
}