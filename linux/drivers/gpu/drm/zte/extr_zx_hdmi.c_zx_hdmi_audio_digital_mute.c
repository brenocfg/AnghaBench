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
struct zx_hdmi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPI_AUD_CONFIG ; 
 int /*<<< orphan*/  TPI_AUD_MUTE ; 
 struct zx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_writeb_mask (struct zx_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_hdmi_audio_digital_mute(struct device *dev, void *data,
				      bool enable)
{
	struct zx_hdmi *hdmi = dev_get_drvdata(dev);

	if (enable)
		hdmi_writeb_mask(hdmi, TPI_AUD_CONFIG, TPI_AUD_MUTE,
				 TPI_AUD_MUTE);
	else
		hdmi_writeb_mask(hdmi, TPI_AUD_CONFIG, TPI_AUD_MUTE, 0);

	return 0;
}