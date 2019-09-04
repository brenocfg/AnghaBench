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
typedef  int u8 ;
struct sun4i_dma_vchan {int is_dedicated; int endpoint; } ;
struct sun4i_dma_dev {int /*<<< orphan*/  slave; } ;
struct of_phandle_args {int* args; } ;
struct of_dma {struct sun4i_dma_dev* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int SUN4I_DDMA_DRQ_TYPE_LIMIT ; 
 int SUN4I_NDMA_DRQ_TYPE_LIMIT ; 
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 struct sun4i_dma_vchan* to_sun4i_dma_vchan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *sun4i_dma_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct sun4i_dma_dev *priv = ofdma->of_dma_data;
	struct sun4i_dma_vchan *vchan;
	struct dma_chan *chan;
	u8 is_dedicated = dma_spec->args[0];
	u8 endpoint = dma_spec->args[1];

	/* Check if type is Normal or Dedicated */
	if (is_dedicated != 0 && is_dedicated != 1)
		return NULL;

	/* Make sure the endpoint looks sane */
	if ((is_dedicated && endpoint >= SUN4I_DDMA_DRQ_TYPE_LIMIT) ||
	    (!is_dedicated && endpoint >= SUN4I_NDMA_DRQ_TYPE_LIMIT))
		return NULL;

	chan = dma_get_any_slave_channel(&priv->slave);
	if (!chan)
		return NULL;

	/* Assign the endpoint to the vchan */
	vchan = to_sun4i_dma_vchan(chan);
	vchan->is_dedicated = is_dedicated;
	vchan->endpoint = endpoint;

	return chan;
}