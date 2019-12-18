#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tda998x_priv {scalar_t__* audio_port_enable; TYPE_1__* hdmi; } ;
struct tda998x_audio_settings {scalar_t__ ena_ap; int /*<<< orphan*/ * route; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * tda998x_audio_route ; 

__attribute__((used)) static int tda998x_derive_routing(struct tda998x_priv *priv,
				  struct tda998x_audio_settings *s,
				  unsigned int route)
{
	s->route = &tda998x_audio_route[route];
	s->ena_ap = priv->audio_port_enable[route];
	if (s->ena_ap == 0) {
		dev_err(&priv->hdmi->dev, "no audio configuration found\n");
		return -EINVAL;
	}

	return 0;
}