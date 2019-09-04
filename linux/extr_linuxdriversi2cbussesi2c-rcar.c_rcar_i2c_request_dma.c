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
struct rcar_i2c_priv {struct dma_chan* dma_tx; struct dma_chan* dma_rx; TYPE_1__* res; } ;
struct i2c_msg {int flags; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int I2C_M_RD ; 
 scalar_t__ ICRXTX ; 
 int /*<<< orphan*/  PTR_ERR (struct dma_chan*) ; 
 struct device* rcar_i2c_priv_to_dev (struct rcar_i2c_priv*) ; 
 struct dma_chan* rcar_i2c_request_dma_chan (struct device*,int,scalar_t__) ; 

__attribute__((used)) static void rcar_i2c_request_dma(struct rcar_i2c_priv *priv,
				 struct i2c_msg *msg)
{
	struct device *dev = rcar_i2c_priv_to_dev(priv);
	bool read;
	struct dma_chan *chan;
	enum dma_transfer_direction dir;

	read = msg->flags & I2C_M_RD;

	chan = read ? priv->dma_rx : priv->dma_tx;
	if (PTR_ERR(chan) != -EPROBE_DEFER)
		return;

	dir = read ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
	chan = rcar_i2c_request_dma_chan(dev, dir, priv->res->start + ICRXTX);

	if (read)
		priv->dma_rx = chan;
	else
		priv->dma_tx = chan;
}