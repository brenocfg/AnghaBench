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
struct tda998x_priv {int /*<<< orphan*/  audio_pdev; scalar_t__* audio_port_enable; } ;
struct hdmi_codec_pdata {int max_i2s_channels; int i2s; int spdif; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  codec_data ;

/* Variables and functions */
 size_t AUDIO_ROUTE_I2S ; 
 size_t AUDIO_ROUTE_SPDIF ; 
 int /*<<< orphan*/  HDMI_CODEC_DRV_NAME ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_codec_ops ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdmi_codec_pdata*,int) ; 

__attribute__((used)) static int tda998x_audio_codec_init(struct tda998x_priv *priv,
				    struct device *dev)
{
	struct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channels = 2,
	};

	if (priv->audio_port_enable[AUDIO_ROUTE_I2S])
		codec_data.i2s = 1;
	if (priv->audio_port_enable[AUDIO_ROUTE_SPDIF])
		codec_data.spdif = 1;

	priv->audio_pdev = platform_device_register_data(
		dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	return PTR_ERR_OR_ZERO(priv->audio_pdev);
}