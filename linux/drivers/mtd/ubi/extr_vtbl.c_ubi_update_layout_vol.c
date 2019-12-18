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
struct ubi_volume {int dummy; } ;
struct ubi_device {int /*<<< orphan*/  vtbl_size; int /*<<< orphan*/  vtbl; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int UBI_LAYOUT_VOLUME_EBS ; 
 int /*<<< orphan*/  UBI_LAYOUT_VOLUME_ID ; 
 int ubi_eba_atomic_leb_change (struct ubi_device*,struct ubi_volume*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t vol_id2idx (struct ubi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubi_update_layout_vol(struct ubi_device *ubi)
{
	struct ubi_volume *layout_vol;
	int i, err;

	layout_vol = ubi->volumes[vol_id2idx(ubi, UBI_LAYOUT_VOLUME_ID)];
	for (i = 0; i < UBI_LAYOUT_VOLUME_EBS; i++) {
		err = ubi_eba_atomic_leb_change(ubi, layout_vol, i, ubi->vtbl,
						ubi->vtbl_size);
		if (err)
			return err;
	}

	return 0;
}