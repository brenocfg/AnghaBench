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
struct vadc_priv {unsigned int nchannels; int /*<<< orphan*/  dev; struct vadc_channel_prop* chan_props; } ;
struct vadc_channel_prop {unsigned int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static struct vadc_channel_prop *vadc_get_channel(struct vadc_priv *vadc,
						  unsigned int num)
{
	unsigned int i;

	for (i = 0; i < vadc->nchannels; i++)
		if (vadc->chan_props[i].channel == num)
			return &vadc->chan_props[i];

	dev_dbg(vadc->dev, "no such channel %02x\n", num);

	return NULL;
}