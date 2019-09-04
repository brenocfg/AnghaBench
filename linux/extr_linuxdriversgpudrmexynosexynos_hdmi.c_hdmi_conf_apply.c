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
struct hdmi_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_audio_config (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_audio_control (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_conf_init (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_mode_apply (struct hdmi_context*) ; 
 int /*<<< orphan*/  hdmi_start (struct hdmi_context*,int) ; 

__attribute__((used)) static void hdmi_conf_apply(struct hdmi_context *hdata)
{
	hdmi_start(hdata, false);
	hdmi_conf_init(hdata);
	hdmi_audio_config(hdata);
	hdmi_mode_apply(hdata);
	hdmi_audio_control(hdata);
}