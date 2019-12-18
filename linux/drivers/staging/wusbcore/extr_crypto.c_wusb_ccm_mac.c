#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct aes_ccm_nonce {int dummy; } ;
struct TYPE_12__ {int flags; scalar_t__ counter; struct aes_ccm_nonce ccm_nonce; } ;
struct TYPE_11__ {int flags; void* lm; struct aes_ccm_nonce ccm_nonce; } ;
struct TYPE_10__ {int /*<<< orphan*/  mac_header; void* la; } ;
struct wusb_mac_scratch {TYPE_3__ ax; TYPE_2__ b0; TYPE_1__ b1; } ;
struct crypto_shash {int dummy; } ;
struct aes_ccm_label {int dummy; } ;
struct aes_ccm_block {int dummy; } ;
struct TYPE_13__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_4__*,struct crypto_shash*) ; 
 void* cpu_to_be16 (size_t) ; 
 int /*<<< orphan*/  crypto_shash_digest (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_finup (TYPE_4__*,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_init (TYPE_4__*) ; 
 int /*<<< orphan*/  crypto_shash_update (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* desc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct aes_ccm_label const*,int) ; 

__attribute__((used)) static int wusb_ccm_mac(struct crypto_shash *tfm_cbcmac,
			struct wusb_mac_scratch *scratch,
			void *mic,
			const struct aes_ccm_nonce *n,
			const struct aes_ccm_label *a, const void *b,
			size_t blen)
{
	SHASH_DESC_ON_STACK(desc, tfm_cbcmac);
	u8 iv[AES_BLOCK_SIZE];

	/*
	 * These checks should be compile time optimized out
	 * ensure @a fills b1's mac_header and following fields
	 */
	BUILD_BUG_ON(sizeof(*a) != sizeof(scratch->b1) - sizeof(scratch->b1.la));
	BUILD_BUG_ON(sizeof(scratch->b0) != sizeof(struct aes_ccm_block));
	BUILD_BUG_ON(sizeof(scratch->b1) != sizeof(struct aes_ccm_block));
	BUILD_BUG_ON(sizeof(scratch->ax) != sizeof(struct aes_ccm_block));

	/* Setup B0 */
	scratch->b0.flags = 0x59;	/* Format B0 */
	scratch->b0.ccm_nonce = *n;
	scratch->b0.lm = cpu_to_be16(0);	/* WUSB1.0[6.5] sez l(m) is 0 */

	/* Setup B1
	 *
	 * The WUSB spec is anything but clear! WUSB1.0[6.5]
	 * says that to initialize B1 from A with 'l(a) = blen +
	 * 14'--after clarification, it means to use A's contents
	 * for MAC Header, EO, sec reserved and padding.
	 */
	scratch->b1.la = cpu_to_be16(blen + 14);
	memcpy(&scratch->b1.mac_header, a, sizeof(*a));

	desc->tfm = tfm_cbcmac;
	crypto_shash_init(desc);
	crypto_shash_update(desc, (u8 *)&scratch->b0, sizeof(scratch->b0) +
						      sizeof(scratch->b1));
	crypto_shash_finup(desc, b, blen, iv);

	/* Now we crypt the MIC Tag (*iv) with Ax -- values per WUSB1.0[6.5]
	 * The procedure is to AES crypt the A0 block and XOR the MIC
	 * Tag against it; we only do the first 8 bytes and place it
	 * directly in the destination buffer.
	 */
	scratch->ax.flags = 0x01;		/* as per WUSB 1.0 spec */
	scratch->ax.ccm_nonce = *n;
	scratch->ax.counter = 0;

	/* reuse the CBC-MAC transform to perform the single block encryption */
	crypto_shash_digest(desc, (u8 *)&scratch->ax, sizeof(scratch->ax),
			    (u8 *)&scratch->ax);

	crypto_xor_cpy(mic, (u8 *)&scratch->ax, iv, 8);

	return 8;
}