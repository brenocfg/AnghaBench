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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dcb_table {int version; } ;
struct TYPE_2__ {struct dcb_table dcb; } ;
struct nouveau_drm {TYPE_1__ vbios; } ;
struct drm_device {int dummy; } ;
struct dcb_output {scalar_t__ type; scalar_t__ location; int i2c_index; } ;

/* Variables and functions */
 scalar_t__ DCB_LOC_ON_CHIP ; 
 scalar_t__ DCB_OUTPUT_TV ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROM32 (int /*<<< orphan*/ ) ; 
 scalar_t__ apply_dcb_encoder_quirks (struct drm_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dcb_output* new_dcb_entry (struct dcb_table*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int parse_dcb15_entry (struct drm_device*,struct dcb_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dcb_output*) ; 
 int parse_dcb20_entry (struct drm_device*,struct dcb_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dcb_output*) ; 

__attribute__((used)) static int
parse_dcb_entry(struct drm_device *dev, void *data, int idx, u8 *outp)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct dcb_table *dcb = &drm->vbios.dcb;
	u32 conf = (dcb->version >= 0x20) ? ROM32(outp[4]) : ROM32(outp[6]);
	u32 conn = ROM32(outp[0]);
	bool ret;

	if (apply_dcb_encoder_quirks(dev, idx, &conn, &conf)) {
		struct dcb_output *entry = new_dcb_entry(dcb);

		NV_INFO(drm, "DCB outp %02d: %08x %08x\n", idx, conn, conf);

		if (dcb->version >= 0x20)
			ret = parse_dcb20_entry(dev, dcb, conn, conf, entry);
		else
			ret = parse_dcb15_entry(dev, dcb, conn, conf, entry);
		if (!ret)
			return 1; /* stop parsing */

		/* Ignore the I2C index for on-chip TV-out, as there
		 * are cards with bogus values (nv31m in bug 23212),
		 * and it's otherwise useless.
		 */
		if (entry->type == DCB_OUTPUT_TV &&
		    entry->location == DCB_LOC_ON_CHIP)
			entry->i2c_index = 0x0f;
	}

	return 0;
}