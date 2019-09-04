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
struct iv_tcw_private {void* whitening; void* iv_seed; int /*<<< orphan*/  crc32_tfm; } ;
struct dm_target {char* error; } ;
struct TYPE_2__ {struct iv_tcw_private tcw; } ;
struct crypt_config {int sector_size; scalar_t__ key_size; scalar_t__ iv_size; TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 scalar_t__ TCW_WHITENING_SIZE ; 
 int /*<<< orphan*/  crypt_iv_tcw_dtr (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_tcw_ctr(struct crypt_config *cc, struct dm_target *ti,
			    const char *opts)
{
	struct iv_tcw_private *tcw = &cc->iv_gen_private.tcw;

	if (cc->sector_size != (1 << SECTOR_SHIFT)) {
		ti->error = "Unsupported sector size for TCW";
		return -EINVAL;
	}

	if (cc->key_size <= (cc->iv_size + TCW_WHITENING_SIZE)) {
		ti->error = "Wrong key size for TCW";
		return -EINVAL;
	}

	tcw->crc32_tfm = crypto_alloc_shash("crc32", 0, 0);
	if (IS_ERR(tcw->crc32_tfm)) {
		ti->error = "Error initializing CRC32 in TCW";
		return PTR_ERR(tcw->crc32_tfm);
	}

	tcw->iv_seed = kzalloc(cc->iv_size, GFP_KERNEL);
	tcw->whitening = kzalloc(TCW_WHITENING_SIZE, GFP_KERNEL);
	if (!tcw->iv_seed || !tcw->whitening) {
		crypt_iv_tcw_dtr(cc);
		ti->error = "Error allocating seed storage in TCW";
		return -ENOMEM;
	}

	return 0;
}