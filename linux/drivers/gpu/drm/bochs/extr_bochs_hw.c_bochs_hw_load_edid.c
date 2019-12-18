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
typedef  int /*<<< orphan*/  u8 ;
struct bochs_device {int /*<<< orphan*/ * edid; int /*<<< orphan*/  connector; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bochs_get_edid_block (struct bochs_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * drm_do_get_edid (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct bochs_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ),struct bochs_device*) ; 
 int drm_edid_header_is_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int bochs_hw_load_edid(struct bochs_device *bochs)
{
	u8 header[8];

	if (!bochs->mmio)
		return -1;

	/* check header to detect whenever edid support is enabled in qemu */
	bochs_get_edid_block(bochs, header, 0, ARRAY_SIZE(header));
	if (drm_edid_header_is_valid(header) != 8)
		return -1;

	kfree(bochs->edid);
	bochs->edid = drm_do_get_edid(&bochs->connector,
				      bochs_get_edid_block, bochs);
	if (bochs->edid == NULL)
		return -1;

	return 0;
}