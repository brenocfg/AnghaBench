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
struct nvbios {int dummy; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  parse_script_table_pointers (struct nvbios*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_bit_init_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{
	/*
	 * Parses the init table segment that the bit entry points to.
	 *
	 * See parse_script_table_pointers for layout
	 */
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (bitentry->length < 14) {
		NV_ERROR(drm, "Do not understand init table\n");
		return -EINVAL;
	}

	parse_script_table_pointers(bios, bitentry->offset);
	return 0;
}