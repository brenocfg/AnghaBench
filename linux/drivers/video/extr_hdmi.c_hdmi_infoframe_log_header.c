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
struct hdmi_any_infoframe {int /*<<< orphan*/  length; int /*<<< orphan*/  version; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_infoframe_type_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_infoframe_log_header(const char *level,
				      struct device *dev,
				      const struct hdmi_any_infoframe *frame)
{
	hdmi_log("HDMI infoframe: %s, version %u, length %u\n",
		hdmi_infoframe_type_get_name(frame->type),
		frame->version, frame->length);
}