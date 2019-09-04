#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tda998x_priv {TYPE_1__* hdmi; TYPE_2__* audio_port; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ format; scalar_t__ config; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AFMT_I2S ; 
 scalar_t__ AFMT_SPDIF ; 
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ be32_to_cpup (int const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static int tda998x_get_audio_ports(struct tda998x_priv *priv,
				   struct device_node *np)
{
	const u32 *port_data;
	u32 size;
	int i;

	port_data = of_get_property(np, "audio-ports", &size);
	if (!port_data)
		return 0;

	size /= sizeof(u32);
	if (size > 2 * ARRAY_SIZE(priv->audio_port) || size % 2 != 0) {
		dev_err(&priv->hdmi->dev,
			"Bad number of elements in audio-ports dt-property\n");
		return -EINVAL;
	}

	size /= 2;

	for (i = 0; i < size; i++) {
		u8 afmt = be32_to_cpup(&port_data[2*i]);
		u8 ena_ap = be32_to_cpup(&port_data[2*i+1]);

		if (afmt != AFMT_SPDIF && afmt != AFMT_I2S) {
			dev_err(&priv->hdmi->dev,
				"Bad audio format %u\n", afmt);
			return -EINVAL;
		}

		priv->audio_port[i].format = afmt;
		priv->audio_port[i].config = ena_ap;
	}

	if (priv->audio_port[0].format == priv->audio_port[1].format) {
		dev_err(&priv->hdmi->dev,
			"There can only be on I2S port and one SPDIF port\n");
		return -EINVAL;
	}
	return 0;
}