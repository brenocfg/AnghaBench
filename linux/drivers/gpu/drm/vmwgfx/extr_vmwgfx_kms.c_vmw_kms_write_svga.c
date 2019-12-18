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
struct vmw_private {int capabilities; scalar_t__ mmio_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,unsigned int,unsigned int) ; 
 int EINVAL ; 
 int SVGA_CAP_PITCHLOCK ; 
 scalar_t__ SVGA_FIFO_PITCHLOCK ; 
 int /*<<< orphan*/  SVGA_REG_BITS_PER_PIXEL ; 
 int /*<<< orphan*/  SVGA_REG_DEPTH ; 
 int /*<<< orphan*/  SVGA_REG_HEIGHT ; 
 int /*<<< orphan*/  SVGA_REG_PITCHLOCK ; 
 int /*<<< orphan*/  SVGA_REG_WIDTH ; 
 scalar_t__ vmw_fifo_have_pitchlock (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_mmio_write (unsigned int,scalar_t__) ; 
 unsigned int vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,unsigned int) ; 

int vmw_kms_write_svga(struct vmw_private *vmw_priv,
			unsigned width, unsigned height, unsigned pitch,
			unsigned bpp, unsigned depth)
{
	if (vmw_priv->capabilities & SVGA_CAP_PITCHLOCK)
		vmw_write(vmw_priv, SVGA_REG_PITCHLOCK, pitch);
	else if (vmw_fifo_have_pitchlock(vmw_priv))
		vmw_mmio_write(pitch, vmw_priv->mmio_virt +
			       SVGA_FIFO_PITCHLOCK);
	vmw_write(vmw_priv, SVGA_REG_WIDTH, width);
	vmw_write(vmw_priv, SVGA_REG_HEIGHT, height);
	vmw_write(vmw_priv, SVGA_REG_BITS_PER_PIXEL, bpp);

	if (vmw_read(vmw_priv, SVGA_REG_DEPTH) != depth) {
		DRM_ERROR("Invalid depth %u for %u bpp, host expects %u\n",
			  depth, bpp, vmw_read(vmw_priv, SVGA_REG_DEPTH));
		return -EINVAL;
	}

	return 0;
}