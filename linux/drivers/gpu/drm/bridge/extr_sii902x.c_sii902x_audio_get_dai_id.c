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
struct snd_soc_component {int dummy; } ;
struct of_endpoint {scalar_t__ port; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SII902X_AUDIO_PORT_INDEX ; 
 int of_graph_parse_endpoint (struct device_node*,struct of_endpoint*) ; 

__attribute__((used)) static int sii902x_audio_get_dai_id(struct snd_soc_component *component,
				    struct device_node *endpoint)
{
	struct of_endpoint of_ep;
	int ret;

	ret = of_graph_parse_endpoint(endpoint, &of_ep);
	if (ret < 0)
		return ret;

	/*
	 * HDMI sound should be located at reg = <3>
	 * Return expected DAI index 0.
	 */
	if (of_ep.port == SII902X_AUDIO_PORT_INDEX)
		return 0;

	return -EINVAL;
}