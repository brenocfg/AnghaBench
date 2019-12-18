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
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__* dev; int /*<<< orphan*/  bad_edid_counter; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_UT_KMS ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int drm_debug ; 
 int /*<<< orphan*/  drm_edid_block_valid (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_edid_is_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void connector_bad_edid(struct drm_connector *connector,
			       u8 *edid, int num_blocks)
{
	int i;

	if (connector->bad_edid_counter++ && !(drm_debug & DRM_UT_KMS))
		return;

	dev_warn(connector->dev->dev,
		 "%s: EDID is invalid:\n",
		 connector->name);
	for (i = 0; i < num_blocks; i++) {
		u8 *block = edid + i * EDID_LENGTH;
		char prefix[20];

		if (drm_edid_is_zero(block, EDID_LENGTH))
			sprintf(prefix, "\t[%02x] ZERO ", i);
		else if (!drm_edid_block_valid(block, i, false, NULL))
			sprintf(prefix, "\t[%02x] BAD  ", i);
		else
			sprintf(prefix, "\t[%02x] GOOD ", i);

		print_hex_dump(KERN_WARNING,
			       prefix, DUMP_PREFIX_NONE, 16, 1,
			       block, EDID_LENGTH, false);
	}
}