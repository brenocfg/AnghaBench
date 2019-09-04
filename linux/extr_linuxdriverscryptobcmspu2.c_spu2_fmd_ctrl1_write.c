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
typedef  int u64 ;
struct SPU2_FMD {int /*<<< orphan*/  ctrl1; } ;

/* Variables and functions */
 int SPU2_CIPH_KEY_LEN ; 
 int SPU2_CIPH_KEY_LEN_SHIFT ; 
 int SPU2_GENIV ; 
 int SPU2_HASH_IV ; 
 int SPU2_HASH_KEY_LEN ; 
 int SPU2_HASH_KEY_LEN_SHIFT ; 
 int SPU2_HASH_TAG_LEN ; 
 int SPU2_HASH_TAG_LEN_SHIFT ; 
 int SPU2_HAS_AAD2 ; 
 int SPU2_IV_LEN ; 
 int SPU2_IV_LEN_SHIFT ; 
 int SPU2_IV_OFFSET_SHIFT ; 
 int SPU2_RETURN_AAD2 ; 
 int SPU2_RETURN_MD_SHIFT ; 
 int SPU2_RETURN_PAY ; 
 scalar_t__ SPU2_RET_FMD_ONLY ; 
 int SPU2_RET_IV ; 
 int SPU2_RET_IV_LEN_SHIFT ; 
 scalar_t__ SPU2_RET_NO_MD ; 
 int SPU2_TAG_LOC ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void spu2_fmd_ctrl1_write(struct SPU2_FMD *fmd, bool is_inbound,
				 u64 assoc_size,
				 u64 auth_key_len, u64 cipher_key_len,
				 bool gen_iv, bool hash_iv, bool return_iv,
				 u64 ret_iv_len, u64 ret_iv_offset,
				 u64 cipher_iv_len, u64 digest_size,
				 bool return_payload, bool return_md)
{
	u64 ctrl1 = 0;

	if (is_inbound && digest_size)
		ctrl1 |= SPU2_TAG_LOC;

	if (assoc_size) {
		ctrl1 |= SPU2_HAS_AAD2;
		ctrl1 |= SPU2_RETURN_AAD2;  /* need aad2 for gcm aes esp */
	}

	if (auth_key_len)
		ctrl1 |= ((auth_key_len << SPU2_HASH_KEY_LEN_SHIFT) &
			  SPU2_HASH_KEY_LEN);

	if (cipher_key_len)
		ctrl1 |= ((cipher_key_len << SPU2_CIPH_KEY_LEN_SHIFT) &
			  SPU2_CIPH_KEY_LEN);

	if (gen_iv)
		ctrl1 |= SPU2_GENIV;

	if (hash_iv)
		ctrl1 |= SPU2_HASH_IV;

	if (return_iv) {
		ctrl1 |= SPU2_RET_IV;
		ctrl1 |= ret_iv_len << SPU2_RET_IV_LEN_SHIFT;
		ctrl1 |= ret_iv_offset << SPU2_IV_OFFSET_SHIFT;
	}

	ctrl1 |= ((cipher_iv_len << SPU2_IV_LEN_SHIFT) & SPU2_IV_LEN);

	if (digest_size)
		ctrl1 |= ((digest_size << SPU2_HASH_TAG_LEN_SHIFT) &
			  SPU2_HASH_TAG_LEN);

	/* Let's ask for the output pkt to include FMD, but don't need to
	 * get keys and IVs back in OMD.
	 */
	if (return_md)
		ctrl1 |= ((u64)SPU2_RET_FMD_ONLY << SPU2_RETURN_MD_SHIFT);
	else
		ctrl1 |= ((u64)SPU2_RET_NO_MD << SPU2_RETURN_MD_SHIFT);

	/* Crypto API does not get assoc data back. So no need for AAD2. */

	if (return_payload)
		ctrl1 |= SPU2_RETURN_PAY;

	fmd->ctrl1 = cpu_to_le64(ctrl1);
}