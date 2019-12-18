#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int dummy; } ;
struct dm_target {char* error; int /*<<< orphan*/  table; } ;
struct crypt_config {scalar_t__ on_disk_tag_size; scalar_t__ sector_size; scalar_t__ integrity_tag_size; scalar_t__ integrity_iv_size; TYPE_2__* dev; } ;
struct blk_integrity {scalar_t__ tag_size; scalar_t__ tuple_size; scalar_t__ interval_exp; TYPE_3__* profile; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__* bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDEBUG (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  any_tfm_aead (struct crypt_config*) ; 
 struct blk_integrity* blk_get_integrity (int /*<<< orphan*/ ) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 scalar_t__ crypto_aead_setauthsize (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dm_device_name (struct mapped_device*) ; 
 struct mapped_device* dm_table_get_md (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int crypt_integrity_ctr(struct crypt_config *cc, struct dm_target *ti)
{
#ifdef CONFIG_BLK_DEV_INTEGRITY
	struct blk_integrity *bi = blk_get_integrity(cc->dev->bdev->bd_disk);
	struct mapped_device *md = dm_table_get_md(ti->table);

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
		DMDEBUG("%s: Integrity AEAD, tag size %u, IV size %u.", dm_device_name(md),
		       cc->integrity_tag_size, cc->integrity_iv_size);

		if (crypto_aead_setauthsize(any_tfm_aead(cc), cc->integrity_tag_size)) {
			ti->error = "Integrity AEAD auth tag size is not supported.";
			return -EINVAL;
		}
	} else if (cc->integrity_iv_size)
		DMDEBUG("%s: Additional per-sector space %u bytes for IV.", dm_device_name(md),
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