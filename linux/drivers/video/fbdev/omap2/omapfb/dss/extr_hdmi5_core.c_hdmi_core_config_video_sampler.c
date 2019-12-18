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
struct hdmi_core_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CORE_TX_INVID0 ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_core_config_video_sampler(struct hdmi_core_data *core)
{
	int video_mapping = 1;	/* for 24 bit color depth */

	/* VIDEO_MAPPING */
	REG_FLD_MOD(core->base, HDMI_CORE_TX_INVID0, video_mapping, 4, 0);
}