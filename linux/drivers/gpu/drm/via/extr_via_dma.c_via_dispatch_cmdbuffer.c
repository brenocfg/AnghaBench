#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_8__ {int /*<<< orphan*/ * virtual_start; } ;
struct TYPE_9__ {int dma_low; scalar_t__ pci_buf; TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_via_private_t ;
struct TYPE_10__ {int size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ drm_via_cmdbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int EFAULT ; 
 int ENOMEM ; 
 int VIA_PCI_BUF_SIZE ; 
 scalar_t__ copy_from_user (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/ * via_check_dma (TYPE_2__*,int) ; 
 int /*<<< orphan*/  via_cmdbuf_pause (TYPE_2__*) ; 
 int /*<<< orphan*/  via_pad_cache (TYPE_2__*,int) ; 
 int via_verify_command_stream (int /*<<< orphan*/ *,int,struct drm_device*,int) ; 

__attribute__((used)) static int via_dispatch_cmdbuffer(struct drm_device *dev, drm_via_cmdbuffer_t *cmd)
{
	drm_via_private_t *dev_priv;
	uint32_t *vb;
	int ret;

	dev_priv = (drm_via_private_t *) dev->dev_private;

	if (dev_priv->ring.virtual_start == NULL) {
		DRM_ERROR("called without initializing AGP ring buffer.\n");
		return -EFAULT;
	}

	if (cmd->size > VIA_PCI_BUF_SIZE)
		return -ENOMEM;

	if (copy_from_user(dev_priv->pci_buf, cmd->buf, cmd->size))
		return -EFAULT;

	/*
	 * Running this function on AGP memory is dead slow. Therefore
	 * we run it on a temporary cacheable system memory buffer and
	 * copy it to AGP memory when ready.
	 */

	if ((ret =
	     via_verify_command_stream((uint32_t *) dev_priv->pci_buf,
				       cmd->size, dev, 1))) {
		return ret;
	}

	vb = via_check_dma(dev_priv, (cmd->size < 0x100) ? 0x102 : cmd->size);
	if (vb == NULL)
		return -EAGAIN;

	memcpy(vb, dev_priv->pci_buf, cmd->size);

	dev_priv->dma_low += cmd->size;

	/*
	 * Small submissions somehow stalls the CPU. (AGP cache effects?)
	 * pad to greater size.
	 */

	if (cmd->size < 0x100)
		via_pad_cache(dev_priv, (0x100 - cmd->size) >> 3);
	via_cmdbuf_pause(dev_priv);

	return 0;
}