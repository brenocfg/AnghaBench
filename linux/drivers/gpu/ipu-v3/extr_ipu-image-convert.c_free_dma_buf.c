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
struct ipu_image_convert_priv {TYPE_1__* ipu; } ;
struct ipu_image_convert_dma_buf {scalar_t__ phys; int /*<<< orphan*/ * virt; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void free_dma_buf(struct ipu_image_convert_priv *priv,
			 struct ipu_image_convert_dma_buf *buf)
{
	if (buf->virt)
		dma_free_coherent(priv->ipu->dev,
				  buf->len, buf->virt, buf->phys);
	buf->virt = NULL;
	buf->phys = 0;
}