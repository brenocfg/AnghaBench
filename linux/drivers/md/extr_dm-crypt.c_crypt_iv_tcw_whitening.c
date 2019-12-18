#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iv_tcw_private {int /*<<< orphan*/  crc32_tfm; scalar_t__ whitening; } ;
struct dm_crypt_request {int /*<<< orphan*/  iv_sector; } ;
struct TYPE_7__ {struct iv_tcw_private tcw; } ;
struct crypt_config {TYPE_1__ iv_gen_private; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_8__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TCW_WHITENING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int crypto_shash_final (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int crypto_shash_init (TYPE_2__*) ; 
 int crypto_shash_update (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* desc ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypt_iv_tcw_whitening(struct crypt_config *cc,
				  struct dm_crypt_request *dmreq,
				  u8 *data)
{
	struct iv_tcw_private *tcw = &cc->iv_gen_private.tcw;
	__le64 sector = cpu_to_le64(dmreq->iv_sector);
	u8 buf[TCW_WHITENING_SIZE];
	SHASH_DESC_ON_STACK(desc, tcw->crc32_tfm);
	int i, r;

	/* xor whitening with sector number */
	crypto_xor_cpy(buf, tcw->whitening, (u8 *)&sector, 8);
	crypto_xor_cpy(&buf[8], tcw->whitening + 8, (u8 *)&sector, 8);

	/* calculate crc32 for every 32bit part and xor it */
	desc->tfm = tcw->crc32_tfm;
	for (i = 0; i < 4; i++) {
		r = crypto_shash_init(desc);
		if (r)
			goto out;
		r = crypto_shash_update(desc, &buf[i * 4], 4);
		if (r)
			goto out;
		r = crypto_shash_final(desc, &buf[i * 4]);
		if (r)
			goto out;
	}
	crypto_xor(&buf[0], &buf[12], 4);
	crypto_xor(&buf[4], &buf[8], 4);

	/* apply whitening (8 bytes) to whole sector */
	for (i = 0; i < ((1 << SECTOR_SHIFT) / 8); i++)
		crypto_xor(data + i * 8, buf, 8);
out:
	memzero_explicit(buf, sizeof(buf));
	return r;
}