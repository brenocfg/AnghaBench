#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_28__ {scalar_t__ staged_bindings; } ;
struct TYPE_30__ {TYPE_5__* man; } ;
struct TYPE_20__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_23__ {int /*<<< orphan*/  object; } ;
struct TYPE_24__ {TYPE_2__ ref; } ;
struct TYPE_22__ {int /*<<< orphan*/  object; } ;
struct TYPE_29__ {int /*<<< orphan*/  lock; } ;
struct vmw_private {unsigned long vmw_chipset; int assume_16bpp; int capabilities; int capabilities2; int vram_size; int mmio_size; int memory_size; int max_mob_pages; int prim_bb_mem; int texture_max_width; int texture_max_height; int stealth; int has_gmr; int has_mob; int has_dx; TYPE_7__ ctx; int /*<<< orphan*/ * res_idr; int /*<<< orphan*/ * mmio_virt; int /*<<< orphan*/ * tdev; struct drm_device* dev; int /*<<< orphan*/ * fman; TYPE_9__ bdev; TYPE_13__ pm_nb; scalar_t__ enable_fb; scalar_t__ has_sm4_1; int /*<<< orphan*/  cap_lock; TYPE_3__ bo_global_ref; TYPE_1__ mem_global_ref; void* mmio_start; TYPE_8__ fbdev_master; TYPE_8__* active_master; void* vram_start; scalar_t__ max_gmr_pages; scalar_t__ max_gmr_ids; scalar_t__ stdu_max_height; scalar_t__ stdu_max_width; scalar_t__ max_mob_size; scalar_t__ fb_max_height; scalar_t__ fb_max_width; void* io_start; scalar_t__ used_memory_size; scalar_t__ fifo_queue_waiters; scalar_t__ fence_queue_waiters; int /*<<< orphan*/  fifo_queue; int /*<<< orphan*/  fence_queue; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/ * res_lru; int /*<<< orphan*/  cursor_lock; int /*<<< orphan*/  svga_lock; int /*<<< orphan*/  waiter_lock; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  resource_lock; int /*<<< orphan*/  global_kms_state_mutex; int /*<<< orphan*/  requested_layout_mutex; int /*<<< orphan*/  binding_mutex; int /*<<< orphan*/  release_mutex; int /*<<< orphan*/  cmdbuf_mutex; scalar_t__ last_read_seqno; } ;
struct drm_device {TYPE_14__* pdev; TYPE_6__* driver; TYPE_4__* anon_inode; struct vmw_private* dev_private; } ;
typedef  int /*<<< orphan*/  host_log ;
typedef  enum vmw_res_type { ____Placeholder_vmw_res_type } vmw_res_type ;
struct TYPE_27__ {int driver_features; } ;
struct TYPE_26__ {int use_type; } ;
struct TYPE_25__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_21__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SVGA3D_DEVCAP_DXCONTEXT ; 
 scalar_t__ SVGA3D_DEVCAP_MAX_TEXTURE_HEIGHT ; 
 scalar_t__ SVGA3D_DEVCAP_MAX_TEXTURE_WIDTH ; 
 scalar_t__ SVGA3D_DEVCAP_SM41 ; 
 int SVGA_CAP2_DX2 ; 
 int SVGA_CAP_3D ; 
 int SVGA_CAP_CAP2_REGISTER ; 
 int SVGA_CAP_DISPLAY_TOPOLOGY ; 
 int SVGA_CAP_GBOBJECTS ; 
 int SVGA_CAP_GMR ; 
 int SVGA_CAP_GMR2 ; 
 int SVGA_CAP_IRQMASK ; 
 int SVGA_CAP_PITCHLOCK ; 
 scalar_t__ SVGA_ID_2 ; 
 int /*<<< orphan*/  SVGA_REG_CAP2 ; 
 int /*<<< orphan*/  SVGA_REG_CAPABILITIES ; 
 int /*<<< orphan*/  SVGA_REG_DEV_CAP ; 
 int /*<<< orphan*/  SVGA_REG_GMRS_MAX_PAGES ; 
 int /*<<< orphan*/  SVGA_REG_GMR_MAX_IDS ; 
 int /*<<< orphan*/  SVGA_REG_ID ; 
 int /*<<< orphan*/  SVGA_REG_MAX_HEIGHT ; 
 int /*<<< orphan*/  SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM ; 
 int /*<<< orphan*/  SVGA_REG_MAX_WIDTH ; 
 int /*<<< orphan*/  SVGA_REG_MEMORY_SIZE ; 
 int /*<<< orphan*/  SVGA_REG_MEM_SIZE ; 
 int /*<<< orphan*/  SVGA_REG_MOB_MAX_SIZE ; 
 int /*<<< orphan*/  SVGA_REG_SCREENTARGET_MAX_HEIGHT ; 
 int /*<<< orphan*/  SVGA_REG_SCREENTARGET_MAX_WIDTH ; 
 int /*<<< orphan*/  SVGA_REG_SUGGESTED_GBOBJECT_MEM_SIZE_KB ; 
 int /*<<< orphan*/  SVGA_REG_VRAM_SIZE ; 
 size_t TTM_PL_VRAM ; 
 int VMWGFX_DRIVER_MAJOR ; 
 int VMWGFX_DRIVER_MINOR ; 
 int VMWGFX_DRIVER_PATCHLEVEL ; 
 int /*<<< orphan*/  VMWGFX_FILE_PAGE_OFFSET ; 
 char* VMWGFX_GIT_VERSION ; 
 char* VMWGFX_REPO ; 
 size_t VMW_PL_GMR ; 
 size_t VMW_PL_MOB ; 
 scalar_t__ enable_fbdev ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_private*) ; 
 struct vmw_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memremap (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_region (TYPE_14__*,int) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_14__*) ; 
 int pci_request_region (TYPE_14__*,int,char*) ; 
 int pci_request_regions (TYPE_14__*,char*) ; 
 void* pci_resource_start (TYPE_14__*,int) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_14__*) ; 
 int /*<<< orphan*/  register_pm_notifier (TYPE_13__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (TYPE_9__*,size_t) ; 
 int ttm_bo_device_init (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_device_release (TYPE_9__*) ; 
 int ttm_bo_init_mm (TYPE_9__*,size_t,size_t) ; 
 int /*<<< orphan*/  ttm_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_lock_set_kill (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ttm_object_device_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_object_device_release (int /*<<< orphan*/ **) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_assume_16bpp ; 
 int /*<<< orphan*/  vmw_binding_state_free (scalar_t__) ; 
 int /*<<< orphan*/  vmw_bo_driver ; 
 int vmw_dma_masks (struct vmw_private*) ; 
 int vmw_dma_select_mode (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fb_init (struct vmw_private*) ; 
 int /*<<< orphan*/ * vmw_fence_manager_init (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fence_manager_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fifo_have_pitchlock (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fifo_resource_inc (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_get_initial_size (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_host_log (char*) ; 
 int vmw_irq_install (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_kms_close (struct vmw_private*) ; 
 int vmw_kms_init (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_master_init (TYPE_8__*) ; 
 int /*<<< orphan*/  vmw_overlay_close (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_overlay_init (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_prime_dmabuf_ops ; 
 int /*<<< orphan*/  vmw_print_capabilities (int) ; 
 int /*<<< orphan*/  vmw_print_capabilities2 (int) ; 
 scalar_t__ vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_request_device (struct vmw_private*) ; 
 int vmw_res_context ; 
 int vmw_res_max ; 
 int /*<<< orphan*/  vmw_svga_enable (struct vmw_private*) ; 
 int vmw_ttm_global_init (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_ttm_global_release (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmwgfx_pm_notifier ; 

__attribute__((used)) static int vmw_driver_load(struct drm_device *dev, unsigned long chipset)
{
	struct vmw_private *dev_priv;
	int ret;
	uint32_t svga_id;
	enum vmw_res_type i;
	bool refuse_dma = false;
	char host_log[100] = {0};

	dev_priv = kzalloc(sizeof(*dev_priv), GFP_KERNEL);
	if (unlikely(!dev_priv)) {
		DRM_ERROR("Failed allocating a device private struct.\n");
		return -ENOMEM;
	}

	pci_set_master(dev->pdev);

	dev_priv->dev = dev;
	dev_priv->vmw_chipset = chipset;
	dev_priv->last_read_seqno = (uint32_t) -100;
	mutex_init(&dev_priv->cmdbuf_mutex);
	mutex_init(&dev_priv->release_mutex);
	mutex_init(&dev_priv->binding_mutex);
	mutex_init(&dev_priv->requested_layout_mutex);
	mutex_init(&dev_priv->global_kms_state_mutex);
	rwlock_init(&dev_priv->resource_lock);
	ttm_lock_init(&dev_priv->reservation_sem);
	spin_lock_init(&dev_priv->hw_lock);
	spin_lock_init(&dev_priv->waiter_lock);
	spin_lock_init(&dev_priv->cap_lock);
	spin_lock_init(&dev_priv->svga_lock);
	spin_lock_init(&dev_priv->cursor_lock);

	for (i = vmw_res_context; i < vmw_res_max; ++i) {
		idr_init(&dev_priv->res_idr[i]);
		INIT_LIST_HEAD(&dev_priv->res_lru[i]);
	}

	mutex_init(&dev_priv->init_mutex);
	init_waitqueue_head(&dev_priv->fence_queue);
	init_waitqueue_head(&dev_priv->fifo_queue);
	dev_priv->fence_queue_waiters = 0;
	dev_priv->fifo_queue_waiters = 0;

	dev_priv->used_memory_size = 0;

	dev_priv->io_start = pci_resource_start(dev->pdev, 0);
	dev_priv->vram_start = pci_resource_start(dev->pdev, 1);
	dev_priv->mmio_start = pci_resource_start(dev->pdev, 2);

	dev_priv->assume_16bpp = !!vmw_assume_16bpp;

	dev_priv->enable_fb = enable_fbdev;

	vmw_write(dev_priv, SVGA_REG_ID, SVGA_ID_2);
	svga_id = vmw_read(dev_priv, SVGA_REG_ID);
	if (svga_id != SVGA_ID_2) {
		ret = -ENOSYS;
		DRM_ERROR("Unsupported SVGA ID 0x%x\n", svga_id);
		goto out_err0;
	}

	dev_priv->capabilities = vmw_read(dev_priv, SVGA_REG_CAPABILITIES);

	if (dev_priv->capabilities & SVGA_CAP_CAP2_REGISTER) {
		dev_priv->capabilities2 = vmw_read(dev_priv, SVGA_REG_CAP2);
	}


	ret = vmw_dma_select_mode(dev_priv);
	if (unlikely(ret != 0)) {
		DRM_INFO("Restricting capabilities due to IOMMU setup.\n");
		refuse_dma = true;
	}

	dev_priv->vram_size = vmw_read(dev_priv, SVGA_REG_VRAM_SIZE);
	dev_priv->mmio_size = vmw_read(dev_priv, SVGA_REG_MEM_SIZE);
	dev_priv->fb_max_width = vmw_read(dev_priv, SVGA_REG_MAX_WIDTH);
	dev_priv->fb_max_height = vmw_read(dev_priv, SVGA_REG_MAX_HEIGHT);

	vmw_get_initial_size(dev_priv);

	if (dev_priv->capabilities & SVGA_CAP_GMR2) {
		dev_priv->max_gmr_ids =
			vmw_read(dev_priv, SVGA_REG_GMR_MAX_IDS);
		dev_priv->max_gmr_pages =
			vmw_read(dev_priv, SVGA_REG_GMRS_MAX_PAGES);
		dev_priv->memory_size =
			vmw_read(dev_priv, SVGA_REG_MEMORY_SIZE);
		dev_priv->memory_size -= dev_priv->vram_size;
	} else {
		/*
		 * An arbitrary limit of 512MiB on surface
		 * memory. But all HWV8 hardware supports GMR2.
		 */
		dev_priv->memory_size = 512*1024*1024;
	}
	dev_priv->max_mob_pages = 0;
	dev_priv->max_mob_size = 0;
	if (dev_priv->capabilities & SVGA_CAP_GBOBJECTS) {
		uint64_t mem_size =
			vmw_read(dev_priv,
				 SVGA_REG_SUGGESTED_GBOBJECT_MEM_SIZE_KB);

		/*
		 * Workaround for low memory 2D VMs to compensate for the
		 * allocation taken by fbdev
		 */
		if (!(dev_priv->capabilities & SVGA_CAP_3D))
			mem_size *= 3;

		dev_priv->max_mob_pages = mem_size * 1024 / PAGE_SIZE;
		dev_priv->prim_bb_mem =
			vmw_read(dev_priv,
				 SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM);
		dev_priv->max_mob_size =
			vmw_read(dev_priv, SVGA_REG_MOB_MAX_SIZE);
		dev_priv->stdu_max_width =
			vmw_read(dev_priv, SVGA_REG_SCREENTARGET_MAX_WIDTH);
		dev_priv->stdu_max_height =
			vmw_read(dev_priv, SVGA_REG_SCREENTARGET_MAX_HEIGHT);

		vmw_write(dev_priv, SVGA_REG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTURE_WIDTH);
		dev_priv->texture_max_width = vmw_read(dev_priv,
						       SVGA_REG_DEV_CAP);
		vmw_write(dev_priv, SVGA_REG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTURE_HEIGHT);
		dev_priv->texture_max_height = vmw_read(dev_priv,
							SVGA_REG_DEV_CAP);
	} else {
		dev_priv->texture_max_width = 8192;
		dev_priv->texture_max_height = 8192;
		dev_priv->prim_bb_mem = dev_priv->vram_size;
	}

	vmw_print_capabilities(dev_priv->capabilities);
	if (dev_priv->capabilities & SVGA_CAP_CAP2_REGISTER)
		vmw_print_capabilities2(dev_priv->capabilities2);

	ret = vmw_dma_masks(dev_priv);
	if (unlikely(ret != 0))
		goto out_err0;

	if (dev_priv->capabilities & SVGA_CAP_GMR2) {
		DRM_INFO("Max GMR ids is %u\n",
			 (unsigned)dev_priv->max_gmr_ids);
		DRM_INFO("Max number of GMR pages is %u\n",
			 (unsigned)dev_priv->max_gmr_pages);
		DRM_INFO("Max dedicated hypervisor surface memory is %u kiB\n",
			 (unsigned)dev_priv->memory_size / 1024);
	}
	DRM_INFO("Maximum display memory size is %u kiB\n",
		 dev_priv->prim_bb_mem / 1024);
	DRM_INFO("VRAM at 0x%08x size is %u kiB\n",
		 dev_priv->vram_start, dev_priv->vram_size / 1024);
	DRM_INFO("MMIO at 0x%08x size is %u kiB\n",
		 dev_priv->mmio_start, dev_priv->mmio_size / 1024);

	ret = vmw_ttm_global_init(dev_priv);
	if (unlikely(ret != 0))
		goto out_err0;


	vmw_master_init(&dev_priv->fbdev_master);
	ttm_lock_set_kill(&dev_priv->fbdev_master.lock, false, SIGTERM);
	dev_priv->active_master = &dev_priv->fbdev_master;

	dev_priv->mmio_virt = memremap(dev_priv->mmio_start,
				       dev_priv->mmio_size, MEMREMAP_WB);

	if (unlikely(dev_priv->mmio_virt == NULL)) {
		ret = -ENOMEM;
		DRM_ERROR("Failed mapping MMIO.\n");
		goto out_err3;
	}

	/* Need mmio memory to check for fifo pitchlock cap. */
	if (!(dev_priv->capabilities & SVGA_CAP_DISPLAY_TOPOLOGY) &&
	    !(dev_priv->capabilities & SVGA_CAP_PITCHLOCK) &&
	    !vmw_fifo_have_pitchlock(dev_priv)) {
		ret = -ENOSYS;
		DRM_ERROR("Hardware has no pitchlock\n");
		goto out_err4;
	}

	dev_priv->tdev = ttm_object_device_init
		(dev_priv->mem_global_ref.object, 12, &vmw_prime_dmabuf_ops);

	if (unlikely(dev_priv->tdev == NULL)) {
		DRM_ERROR("Unable to initialize TTM object management.\n");
		ret = -ENOMEM;
		goto out_err4;
	}

	dev->dev_private = dev_priv;

	ret = pci_request_regions(dev->pdev, "vmwgfx probe");
	dev_priv->stealth = (ret != 0);
	if (dev_priv->stealth) {
		/**
		 * Request at least the mmio PCI resource.
		 */

		DRM_INFO("It appears like vesafb is loaded. "
			 "Ignore above error if any.\n");
		ret = pci_request_region(dev->pdev, 2, "vmwgfx stealth probe");
		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed reserving the SVGA MMIO resource.\n");
			goto out_no_device;
		}
	}

	if (dev_priv->capabilities & SVGA_CAP_IRQMASK) {
		ret = vmw_irq_install(dev, dev->pdev->irq);
		if (ret != 0) {
			DRM_ERROR("Failed installing irq: %d\n", ret);
			goto out_no_irq;
		}
	}

	dev_priv->fman = vmw_fence_manager_init(dev_priv);
	if (unlikely(dev_priv->fman == NULL)) {
		ret = -ENOMEM;
		goto out_no_fman;
	}

	ret = ttm_bo_device_init(&dev_priv->bdev,
				 dev_priv->bo_global_ref.ref.object,
				 &vmw_bo_driver,
				 dev->anon_inode->i_mapping,
				 VMWGFX_FILE_PAGE_OFFSET,
				 false);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed initializing TTM buffer object driver.\n");
		goto out_no_bdev;
	}

	/*
	 * Enable VRAM, but initially don't use it until SVGA is enabled and
	 * unhidden.
	 */
	ret = ttm_bo_init_mm(&dev_priv->bdev, TTM_PL_VRAM,
			     (dev_priv->vram_size >> PAGE_SHIFT));
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed initializing memory manager for VRAM.\n");
		goto out_no_vram;
	}
	dev_priv->bdev.man[TTM_PL_VRAM].use_type = false;

	dev_priv->has_gmr = true;
	if (((dev_priv->capabilities & (SVGA_CAP_GMR | SVGA_CAP_GMR2)) == 0) ||
	    refuse_dma || ttm_bo_init_mm(&dev_priv->bdev, VMW_PL_GMR,
					 VMW_PL_GMR) != 0) {
		DRM_INFO("No GMR memory available. "
			 "Graphics memory resources are very limited.\n");
		dev_priv->has_gmr = false;
	}

	if (dev_priv->capabilities & SVGA_CAP_GBOBJECTS) {
		dev_priv->has_mob = true;
		if (ttm_bo_init_mm(&dev_priv->bdev, VMW_PL_MOB,
				   VMW_PL_MOB) != 0) {
			DRM_INFO("No MOB memory available. "
				 "3D will be disabled.\n");
			dev_priv->has_mob = false;
		}
	}

	if (dev_priv->has_mob) {
		spin_lock(&dev_priv->cap_lock);
		vmw_write(dev_priv, SVGA_REG_DEV_CAP, SVGA3D_DEVCAP_DXCONTEXT);
		dev_priv->has_dx = !!vmw_read(dev_priv, SVGA_REG_DEV_CAP);
		spin_unlock(&dev_priv->cap_lock);
	}


	ret = vmw_kms_init(dev_priv);
	if (unlikely(ret != 0))
		goto out_no_kms;
	vmw_overlay_init(dev_priv);

	ret = vmw_request_device(dev_priv);
	if (ret)
		goto out_no_fifo;

	if (dev_priv->has_dx) {
		/*
		 * SVGA_CAP2_DX2 (DefineGBSurface_v3) is needed for SM4_1
		 * support
		 */
		if ((dev_priv->capabilities2 & SVGA_CAP2_DX2) != 0) {
			vmw_write(dev_priv, SVGA_REG_DEV_CAP,
					SVGA3D_DEVCAP_SM41);
			dev_priv->has_sm4_1 = vmw_read(dev_priv,
							SVGA_REG_DEV_CAP);
		}
	}

	DRM_INFO("DX: %s\n", dev_priv->has_dx ? "yes." : "no.");
	DRM_INFO("Atomic: %s\n", (dev->driver->driver_features & DRIVER_ATOMIC)
		 ? "yes." : "no.");
	DRM_INFO("SM4_1: %s\n", dev_priv->has_sm4_1 ? "yes." : "no.");

	snprintf(host_log, sizeof(host_log), "vmwgfx: %s-%s",
		VMWGFX_REPO, VMWGFX_GIT_VERSION);
	vmw_host_log(host_log);

	memset(host_log, 0, sizeof(host_log));
	snprintf(host_log, sizeof(host_log), "vmwgfx: Module Version: %d.%d.%d",
		VMWGFX_DRIVER_MAJOR, VMWGFX_DRIVER_MINOR,
		VMWGFX_DRIVER_PATCHLEVEL);
	vmw_host_log(host_log);

	if (dev_priv->enable_fb) {
		vmw_fifo_resource_inc(dev_priv);
		vmw_svga_enable(dev_priv);
		vmw_fb_init(dev_priv);
	}

	dev_priv->pm_nb.notifier_call = vmwgfx_pm_notifier;
	register_pm_notifier(&dev_priv->pm_nb);

	return 0;

out_no_fifo:
	vmw_overlay_close(dev_priv);
	vmw_kms_close(dev_priv);
out_no_kms:
	if (dev_priv->has_mob)
		(void) ttm_bo_clean_mm(&dev_priv->bdev, VMW_PL_MOB);
	if (dev_priv->has_gmr)
		(void) ttm_bo_clean_mm(&dev_priv->bdev, VMW_PL_GMR);
	(void)ttm_bo_clean_mm(&dev_priv->bdev, TTM_PL_VRAM);
out_no_vram:
	(void)ttm_bo_device_release(&dev_priv->bdev);
out_no_bdev:
	vmw_fence_manager_takedown(dev_priv->fman);
out_no_fman:
	if (dev_priv->capabilities & SVGA_CAP_IRQMASK)
		vmw_irq_uninstall(dev_priv->dev);
out_no_irq:
	if (dev_priv->stealth)
		pci_release_region(dev->pdev, 2);
	else
		pci_release_regions(dev->pdev);
out_no_device:
	ttm_object_device_release(&dev_priv->tdev);
out_err4:
	memunmap(dev_priv->mmio_virt);
out_err3:
	vmw_ttm_global_release(dev_priv);
out_err0:
	for (i = vmw_res_context; i < vmw_res_max; ++i)
		idr_destroy(&dev_priv->res_idr[i]);

	if (dev_priv->ctx.staged_bindings)
		vmw_binding_state_free(dev_priv->ctx.staged_bindings);
	kfree(dev_priv);
	return ret;
}