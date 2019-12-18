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
struct vbva_modehint {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;
struct vbox_private {scalar_t__ guest_heap; TYPE_1__ ddev; int /*<<< orphan*/  guest_pool; int /*<<< orphan*/  last_mode_hints; int /*<<< orphan*/  num_crtcs; int /*<<< orphan*/  available_vram_size; int /*<<< orphan*/  full_vram_size; int /*<<< orphan*/  any_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GUEST_HEAP_OFFSET (struct vbox_private*) ; 
 int /*<<< orphan*/  GUEST_HEAP_SIZE ; 
 int /*<<< orphan*/  GUEST_HEAP_USABLE_SIZE ; 
 int /*<<< orphan*/  VBE_DISPI_ID_ANYX ; 
 int /*<<< orphan*/  VBE_DISPI_IOPORT_DATA ; 
 int /*<<< orphan*/  VBOX_MAX_SCREENS ; 
 int /*<<< orphan*/  VBOX_VBVA_CONF32_MONITOR_COUNT ; 
 int /*<<< orphan*/  clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int gen_pool_add_virt (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_create (int,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_hgsmi_mode_hints (struct vbox_private*) ; 
 int /*<<< orphan*/  hgsmi_query_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hgsmi_test_query_conf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_iomap_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  u32 ; 
 int vbox_accel_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_check_supported (int /*<<< orphan*/ ) ; 

int vbox_hw_init(struct vbox_private *vbox)
{
	int ret = -ENOMEM;

	vbox->full_vram_size = inl(VBE_DISPI_IOPORT_DATA);
	vbox->any_pitch = vbox_check_supported(VBE_DISPI_ID_ANYX);

	DRM_INFO("VRAM %08x\n", vbox->full_vram_size);

	/* Map guest-heap at end of vram */
	vbox->guest_heap =
	    pci_iomap_range(vbox->ddev.pdev, 0, GUEST_HEAP_OFFSET(vbox),
			    GUEST_HEAP_SIZE);
	if (!vbox->guest_heap)
		return -ENOMEM;

	/* Create guest-heap mem-pool use 2^4 = 16 byte chunks */
	vbox->guest_pool = gen_pool_create(4, -1);
	if (!vbox->guest_pool)
		goto err_unmap_guest_heap;

	ret = gen_pool_add_virt(vbox->guest_pool,
				(unsigned long)vbox->guest_heap,
				GUEST_HEAP_OFFSET(vbox),
				GUEST_HEAP_USABLE_SIZE, -1);
	if (ret)
		goto err_destroy_guest_pool;

	ret = hgsmi_test_query_conf(vbox->guest_pool);
	if (ret) {
		DRM_ERROR("vboxvideo: hgsmi_test_query_conf failed\n");
		goto err_destroy_guest_pool;
	}

	/* Reduce available VRAM size to reflect the guest heap. */
	vbox->available_vram_size = GUEST_HEAP_OFFSET(vbox);
	/* Linux drm represents monitors as a 32-bit array. */
	hgsmi_query_conf(vbox->guest_pool, VBOX_VBVA_CONF32_MONITOR_COUNT,
			 &vbox->num_crtcs);
	vbox->num_crtcs = clamp_t(u32, vbox->num_crtcs, 1, VBOX_MAX_SCREENS);

	if (!have_hgsmi_mode_hints(vbox)) {
		ret = -ENOTSUPP;
		goto err_destroy_guest_pool;
	}

	vbox->last_mode_hints = devm_kcalloc(vbox->ddev.dev, vbox->num_crtcs,
					     sizeof(struct vbva_modehint),
					     GFP_KERNEL);
	if (!vbox->last_mode_hints) {
		ret = -ENOMEM;
		goto err_destroy_guest_pool;
	}

	ret = vbox_accel_init(vbox);
	if (ret)
		goto err_destroy_guest_pool;

	return 0;

err_destroy_guest_pool:
	gen_pool_destroy(vbox->guest_pool);
err_unmap_guest_heap:
	pci_iounmap(vbox->ddev.pdev, vbox->guest_heap);
	return ret;
}