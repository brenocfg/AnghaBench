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
struct vga_device {int decodes; int locks; int owns; scalar_t__ mem_lock_cnt; scalar_t__ io_lock_cnt; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int VGA_RSRC_LEGACY_IO ; 
 int VGA_RSRC_LEGACY_MASK ; 
 int VGA_RSRC_LEGACY_MEM ; 
 int /*<<< orphan*/  __vga_put (struct vga_device*,int) ; 
 int /*<<< orphan*/  vga_decode_count ; 
 int /*<<< orphan*/  vga_iostate_to_str (int) ; 
 int /*<<< orphan*/  vgaarb_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgaarb_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vga_update_device_decodes(struct vga_device *vgadev,
					     int new_decodes)
{
	struct device *dev = &vgadev->pdev->dev;
	int old_decodes, decodes_removed, decodes_unlocked;

	old_decodes = vgadev->decodes;
	decodes_removed = ~new_decodes & old_decodes;
	decodes_unlocked = vgadev->locks & decodes_removed;
	vgadev->decodes = new_decodes;

	vgaarb_info(dev, "changed VGA decodes: olddecodes=%s,decodes=%s:owns=%s\n",
		vga_iostate_to_str(old_decodes),
		vga_iostate_to_str(vgadev->decodes),
		vga_iostate_to_str(vgadev->owns));

	/* if we removed locked decodes, lock count goes to zero, and release */
	if (decodes_unlocked) {
		if (decodes_unlocked & VGA_RSRC_LEGACY_IO)
			vgadev->io_lock_cnt = 0;
		if (decodes_unlocked & VGA_RSRC_LEGACY_MEM)
			vgadev->mem_lock_cnt = 0;
		__vga_put(vgadev, decodes_unlocked);
	}

	/* change decodes counter */
	if (old_decodes & VGA_RSRC_LEGACY_MASK &&
	    !(new_decodes & VGA_RSRC_LEGACY_MASK))
		vga_decode_count--;
	if (!(old_decodes & VGA_RSRC_LEGACY_MASK) &&
	    new_decodes & VGA_RSRC_LEGACY_MASK)
		vga_decode_count++;
	vgaarb_dbg(dev, "decoding count now is: %d\n", vga_decode_count);
}