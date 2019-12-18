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
struct hdmi_config {scalar_t__ hdmi_dvi_mode; } ;

/* Variables and functions */
 scalar_t__ HDMI_HDMI ; 

__attribute__((used)) static inline bool hdmi_mode_has_audio(struct hdmi_config *cfg)
{
	return cfg->hdmi_dvi_mode == HDMI_HDMI ? true : false;
}