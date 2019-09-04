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
struct iv_lmk_private {int /*<<< orphan*/ * seed; int /*<<< orphan*/  hash_tfm; } ;
struct dm_target {char* error; } ;
struct TYPE_2__ {struct iv_lmk_private lmk; } ;
struct crypt_config {int sector_size; scalar_t__ key_parts; scalar_t__ tfms_count; TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMK_SEED_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  crypt_iv_lmk_dtr (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_lmk_ctr(struct crypt_config *cc, struct dm_target *ti,
			    const char *opts)
{
	struct iv_lmk_private *lmk = &cc->iv_gen_private.lmk;

	if (cc->sector_size != (1 << SECTOR_SHIFT)) {
		ti->error = "Unsupported sector size for LMK";
		return -EINVAL;
	}

	lmk->hash_tfm = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(lmk->hash_tfm)) {
		ti->error = "Error initializing LMK hash";
		return PTR_ERR(lmk->hash_tfm);
	}

	/* No seed in LMK version 2 */
	if (cc->key_parts == cc->tfms_count) {
		lmk->seed = NULL;
		return 0;
	}

	lmk->seed = kzalloc(LMK_SEED_SIZE, GFP_KERNEL);
	if (!lmk->seed) {
		crypt_iv_lmk_dtr(cc);
		ti->error = "Error kmallocing seed storage in LMK";
		return -ENOMEM;
	}

	return 0;
}