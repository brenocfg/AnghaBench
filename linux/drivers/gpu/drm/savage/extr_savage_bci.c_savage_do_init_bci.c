#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct drm_device {scalar_t__ agp_buffer_token; TYPE_1__* dma; TYPE_8__* agp_buffer_map; TYPE_4__* dev_private; } ;
typedef  int /*<<< orphan*/  drm_savage_sarea_t ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/  handle; int /*<<< orphan*/  size; scalar_t__ offset; } ;
struct TYPE_13__ {int fb_bpp; int front_pitch; int back_pitch; int depth_bpp; int depth_pitch; scalar_t__ chipset; unsigned int front_bd; unsigned int back_bd; unsigned int depth_bd; int /*<<< orphan*/  emit_clip_rect; int /*<<< orphan*/  wait_evnt; int /*<<< orphan*/  wait_fifo; scalar_t__ volatile* status_ptr; scalar_t__ volatile event_counter; TYPE_3__* status; int /*<<< orphan*/  status_used_mask; TYPE_2__* mmio; scalar_t__ volatile* bci_ptr; scalar_t__ event_wrap; TYPE_9__* sarea; int /*<<< orphan*/ * sarea_priv; int /*<<< orphan*/  dma_flush; TYPE_8__ fake_dma; TYPE_8__* cmd_dma; int /*<<< orphan*/  dma_type; int /*<<< orphan*/ * agp_textures; int /*<<< orphan*/  texture_size; int /*<<< orphan*/  texture_offset; int /*<<< orphan*/  depth_offset; int /*<<< orphan*/  back_offset; int /*<<< orphan*/  front_offset; int /*<<< orphan*/  bci_threshold_hi; int /*<<< orphan*/  bci_threshold_lo; int /*<<< orphan*/  cob_size; } ;
typedef  TYPE_4__ drm_savage_private_t ;
struct TYPE_14__ {int fb_bpp; int depth_bpp; int front_pitch; int back_pitch; int depth_pitch; scalar_t__ status_offset; scalar_t__ buffers_offset; scalar_t__ agp_textures_offset; scalar_t__ cmd_dma_offset; int sarea_priv_offset; int /*<<< orphan*/  texture_size; int /*<<< orphan*/  texture_offset; int /*<<< orphan*/  depth_offset; int /*<<< orphan*/  back_offset; int /*<<< orphan*/  front_offset; int /*<<< orphan*/  dma_type; int /*<<< orphan*/  bci_threshold_hi; int /*<<< orphan*/  bci_threshold_lo; int /*<<< orphan*/  cob_size; } ;
typedef  TYPE_5__ drm_savage_init_t ;
struct TYPE_16__ {scalar_t__ handle; } ;
struct TYPE_12__ {scalar_t__ handle; } ;
struct TYPE_11__ {scalar_t__ handle; } ;
struct TYPE_10__ {scalar_t__ buflist; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ S3_SAVAGE3D_SERIES (scalar_t__) ; 
 scalar_t__ S3_SAVAGE4 ; 
 int SAVAGE_BCI_OFFSET ; 
 unsigned int SAVAGE_BD_BPP_SHIFT ; 
 unsigned int SAVAGE_BD_BW_DISABLE ; 
 unsigned int SAVAGE_BD_TILE_16BPP ; 
 unsigned int SAVAGE_BD_TILE_32BPP ; 
 unsigned int SAVAGE_BD_TILE_DEST ; 
 unsigned int SAVAGE_BD_TILE_SHIFT ; 
 int /*<<< orphan*/  SAVAGE_DMA_AGP ; 
 int /*<<< orphan*/  SAVAGE_DMA_PCI ; 
 int /*<<< orphan*/  SAVAGE_FAKE_DMA_SIZE ; 
 int /*<<< orphan*/  SAVAGE_FIFO_USED_MASK_S3D ; 
 int /*<<< orphan*/  SAVAGE_FIFO_USED_MASK_S4 ; 
 scalar_t__ _DRM_AGP ; 
 scalar_t__ _DRM_CONSISTENT ; 
 scalar_t__ _DRM_SHM ; 
 void* drm_legacy_findmap (struct drm_device*,scalar_t__) ; 
 TYPE_9__* drm_legacy_getsarea (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_ioremap (TYPE_8__*,struct drm_device*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savage_bci_wait_event_reg ; 
 int /*<<< orphan*/  savage_bci_wait_event_shadow ; 
 int /*<<< orphan*/  savage_bci_wait_fifo_s3d ; 
 int /*<<< orphan*/  savage_bci_wait_fifo_s4 ; 
 int /*<<< orphan*/  savage_bci_wait_fifo_shadow ; 
 int /*<<< orphan*/  savage_dma_flush ; 
 scalar_t__ savage_dma_init (TYPE_4__*) ; 
 int /*<<< orphan*/  savage_do_cleanup_bci (struct drm_device*) ; 
 int /*<<< orphan*/  savage_emit_clip_rect_s3d ; 
 int /*<<< orphan*/  savage_emit_clip_rect_s4 ; 
 int /*<<< orphan*/  savage_fake_dma_flush ; 
 scalar_t__ savage_freelist_init (struct drm_device*) ; 

__attribute__((used)) static int savage_do_init_bci(struct drm_device * dev, drm_savage_init_t * init)
{
	drm_savage_private_t *dev_priv = dev->dev_private;

	if (init->fb_bpp != 16 && init->fb_bpp != 32) {
		DRM_ERROR("invalid frame buffer bpp %d!\n", init->fb_bpp);
		return -EINVAL;
	}
	if (init->depth_bpp != 16 && init->depth_bpp != 32) {
		DRM_ERROR("invalid depth buffer bpp %d!\n", init->fb_bpp);
		return -EINVAL;
	}
	if (init->dma_type != SAVAGE_DMA_AGP &&
	    init->dma_type != SAVAGE_DMA_PCI) {
		DRM_ERROR("invalid dma memory type %d!\n", init->dma_type);
		return -EINVAL;
	}

	dev_priv->cob_size = init->cob_size;
	dev_priv->bci_threshold_lo = init->bci_threshold_lo;
	dev_priv->bci_threshold_hi = init->bci_threshold_hi;
	dev_priv->dma_type = init->dma_type;

	dev_priv->fb_bpp = init->fb_bpp;
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;
	dev_priv->depth_bpp = init->depth_bpp;
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->depth_pitch = init->depth_pitch;

	dev_priv->texture_offset = init->texture_offset;
	dev_priv->texture_size = init->texture_size;

	dev_priv->sarea = drm_legacy_getsarea(dev);
	if (!dev_priv->sarea) {
		DRM_ERROR("could not find sarea!\n");
		savage_do_cleanup_bci(dev);
		return -EINVAL;
	}
	if (init->status_offset != 0) {
		dev_priv->status = drm_legacy_findmap(dev, init->status_offset);
		if (!dev_priv->status) {
			DRM_ERROR("could not find shadow status region!\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
	} else {
		dev_priv->status = NULL;
	}
	if (dev_priv->dma_type == SAVAGE_DMA_AGP && init->buffers_offset) {
		dev->agp_buffer_token = init->buffers_offset;
		dev->agp_buffer_map = drm_legacy_findmap(dev,
						       init->buffers_offset);
		if (!dev->agp_buffer_map) {
			DRM_ERROR("could not find DMA buffer region!\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
		drm_legacy_ioremap(dev->agp_buffer_map, dev);
		if (!dev->agp_buffer_map->handle) {
			DRM_ERROR("failed to ioremap DMA buffer region!\n");
			savage_do_cleanup_bci(dev);
			return -ENOMEM;
		}
	}
	if (init->agp_textures_offset) {
		dev_priv->agp_textures =
		    drm_legacy_findmap(dev, init->agp_textures_offset);
		if (!dev_priv->agp_textures) {
			DRM_ERROR("could not find agp texture region!\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
	} else {
		dev_priv->agp_textures = NULL;
	}

	if (init->cmd_dma_offset) {
		if (S3_SAVAGE3D_SERIES(dev_priv->chipset)) {
			DRM_ERROR("command DMA not supported on "
				  "Savage3D/MX/IX.\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
		if (dev->dma && dev->dma->buflist) {
			DRM_ERROR("command and vertex DMA not supported "
				  "at the same time.\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
		dev_priv->cmd_dma = drm_legacy_findmap(dev, init->cmd_dma_offset);
		if (!dev_priv->cmd_dma) {
			DRM_ERROR("could not find command DMA region!\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
		if (dev_priv->dma_type == SAVAGE_DMA_AGP) {
			if (dev_priv->cmd_dma->type != _DRM_AGP) {
				DRM_ERROR("AGP command DMA region is not a "
					  "_DRM_AGP map!\n");
				savage_do_cleanup_bci(dev);
				return -EINVAL;
			}
			drm_legacy_ioremap(dev_priv->cmd_dma, dev);
			if (!dev_priv->cmd_dma->handle) {
				DRM_ERROR("failed to ioremap command "
					  "DMA region!\n");
				savage_do_cleanup_bci(dev);
				return -ENOMEM;
			}
		} else if (dev_priv->cmd_dma->type != _DRM_CONSISTENT) {
			DRM_ERROR("PCI command DMA region is not a "
				  "_DRM_CONSISTENT map!\n");
			savage_do_cleanup_bci(dev);
			return -EINVAL;
		}
	} else {
		dev_priv->cmd_dma = NULL;
	}

	dev_priv->dma_flush = savage_dma_flush;
	if (!dev_priv->cmd_dma) {
		DRM_DEBUG("falling back to faked command DMA.\n");
		dev_priv->fake_dma.offset = 0;
		dev_priv->fake_dma.size = SAVAGE_FAKE_DMA_SIZE;
		dev_priv->fake_dma.type = _DRM_SHM;
		dev_priv->fake_dma.handle = kmalloc(SAVAGE_FAKE_DMA_SIZE,
						    GFP_KERNEL);
		if (!dev_priv->fake_dma.handle) {
			DRM_ERROR("could not allocate faked DMA buffer!\n");
			savage_do_cleanup_bci(dev);
			return -ENOMEM;
		}
		dev_priv->cmd_dma = &dev_priv->fake_dma;
		dev_priv->dma_flush = savage_fake_dma_flush;
	}

	dev_priv->sarea_priv =
	    (drm_savage_sarea_t *) ((uint8_t *) dev_priv->sarea->handle +
				    init->sarea_priv_offset);

	/* setup bitmap descriptors */
	{
		unsigned int color_tile_format;
		unsigned int depth_tile_format;
		unsigned int front_stride, back_stride, depth_stride;
		if (dev_priv->chipset <= S3_SAVAGE4) {
			color_tile_format = dev_priv->fb_bpp == 16 ?
			    SAVAGE_BD_TILE_16BPP : SAVAGE_BD_TILE_32BPP;
			depth_tile_format = dev_priv->depth_bpp == 16 ?
			    SAVAGE_BD_TILE_16BPP : SAVAGE_BD_TILE_32BPP;
		} else {
			color_tile_format = SAVAGE_BD_TILE_DEST;
			depth_tile_format = SAVAGE_BD_TILE_DEST;
		}
		front_stride = dev_priv->front_pitch / (dev_priv->fb_bpp / 8);
		back_stride = dev_priv->back_pitch / (dev_priv->fb_bpp / 8);
		depth_stride =
		    dev_priv->depth_pitch / (dev_priv->depth_bpp / 8);

		dev_priv->front_bd = front_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->fb_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (color_tile_format << SAVAGE_BD_TILE_SHIFT);

		dev_priv->back_bd = back_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->fb_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (color_tile_format << SAVAGE_BD_TILE_SHIFT);

		dev_priv->depth_bd = depth_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->depth_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (depth_tile_format << SAVAGE_BD_TILE_SHIFT);
	}

	/* setup status and bci ptr */
	dev_priv->event_counter = 0;
	dev_priv->event_wrap = 0;
	dev_priv->bci_ptr = (volatile uint32_t *)
	    ((uint8_t *) dev_priv->mmio->handle + SAVAGE_BCI_OFFSET);
	if (S3_SAVAGE3D_SERIES(dev_priv->chipset)) {
		dev_priv->status_used_mask = SAVAGE_FIFO_USED_MASK_S3D;
	} else {
		dev_priv->status_used_mask = SAVAGE_FIFO_USED_MASK_S4;
	}
	if (dev_priv->status != NULL) {
		dev_priv->status_ptr =
		    (volatile uint32_t *)dev_priv->status->handle;
		dev_priv->wait_fifo = savage_bci_wait_fifo_shadow;
		dev_priv->wait_evnt = savage_bci_wait_event_shadow;
		dev_priv->status_ptr[1023] = dev_priv->event_counter;
	} else {
		dev_priv->status_ptr = NULL;
		if (S3_SAVAGE3D_SERIES(dev_priv->chipset)) {
			dev_priv->wait_fifo = savage_bci_wait_fifo_s3d;
		} else {
			dev_priv->wait_fifo = savage_bci_wait_fifo_s4;
		}
		dev_priv->wait_evnt = savage_bci_wait_event_reg;
	}

	/* cliprect functions */
	if (S3_SAVAGE3D_SERIES(dev_priv->chipset))
		dev_priv->emit_clip_rect = savage_emit_clip_rect_s3d;
	else
		dev_priv->emit_clip_rect = savage_emit_clip_rect_s4;

	if (savage_freelist_init(dev) < 0) {
		DRM_ERROR("could not initialize freelist\n");
		savage_do_cleanup_bci(dev);
		return -ENOMEM;
	}

	if (savage_dma_init(dev_priv) < 0) {
		DRM_ERROR("could not initialize command DMA\n");
		savage_do_cleanup_bci(dev);
		return -ENOMEM;
	}

	return 0;
}