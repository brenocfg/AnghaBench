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
struct dm_target {char* error; } ;
struct crypt_config {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int crypt_integrity_ctr(struct crypt_config *cc, struct dm_target *ti)
{
#ifdef CONFIG_BLK_DEV_INTEGRITY
	struct blk_integrity *bi = blk_get_integrity(cc->dev->bdev->bd_disk);

	/* From now we require underlying device with our integrity profile */
	if (!bi || strcasecmp(bi->profile->name, "DM-DIF-EXT-TAG")) {
		ti->error = "Integrity profile not supported.";
		return -EINVAL;
	}

	if (bi->tag_size != cc->on_disk_tag_size ||
	    bi->tuple_size != cc->on_disk_tag_size) {
		ti->error = "Integrity profile tag size mismatch.";
		return -EINVAL;
	}
	if (1 << bi->interval_exp != cc->sector_size) {
		ti->error = "Integrity profile sector size mismatch.";
		return -EINVAL;
	}

	if (crypt_integrity_aead(cc)) {
		cc->integrity_tag_size = cc->on_disk_tag_size - cc->integrity_iv_size;
		DMINFO("Integrity AEAD, tag size %u, IV size %u.",
		       cc->integrity_tag_size, cc->integrity_iv_size);

		if (crypto_aead_setauthsize(any_tfm_aead(cc), cc->integrity_tag_size)) {
			ti->error = "Integrity AEAD auth tag size is not supported.";
			return -EINVAL;
		}
	} else if (cc->integrity_iv_size)
		DMINFO("Additional per-sector space %u bytes for IV.",
		       cc->integrity_iv_size);

	if ((cc->integrity_tag_size + cc->integrity_iv_size) != bi->tag_size) {
		ti->error = "Not enough space for integrity tag in the profile.";
		return -EINVAL;
	}

	return 0;
#else
	ti->error = "Integrity profile not supported.";
	return -EINVAL;
#endif
}