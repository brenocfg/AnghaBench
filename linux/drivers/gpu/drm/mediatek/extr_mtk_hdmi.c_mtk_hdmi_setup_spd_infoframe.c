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
typedef  int /*<<< orphan*/  u8 ;
struct mtk_hdmi {int /*<<< orphan*/  dev; } ;
struct hdmi_spd_infoframe {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ hdmi_spd_infoframe_init (struct hdmi_spd_infoframe*,char const*,char const*) ; 
 scalar_t__ hdmi_spd_infoframe_pack (struct hdmi_spd_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_send_info_frame (struct mtk_hdmi*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtk_hdmi_setup_spd_infoframe(struct mtk_hdmi *hdmi,
					const char *vendor,
					const char *product)
{
	struct hdmi_spd_infoframe frame;
	u8 buffer[29];
	ssize_t err;

	err = hdmi_spd_infoframe_init(&frame, vendor, product);
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to initialize SPD infoframe: %zd\n",
			err);
		return err;
	}

	err = hdmi_spd_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to pack SDP infoframe: %zd\n", err);
		return err;
	}

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, sizeof(buffer));
	return 0;
}