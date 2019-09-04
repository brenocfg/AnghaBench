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
typedef  int u32 ;
typedef  int u16 ;
struct scatter_walk {int /*<<< orphan*/  sg; } ;
struct crypto_aes_ctx {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int assoclen; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ccm_update_mac (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 void* cpu_to_be16 (int) ; 
 struct crypto_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,int) ; 
 int scatterwalk_clamp (struct scatter_walk*,int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccm_calculate_auth_mac(struct aead_request *req, u8 mac[])
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_aes_ctx *ctx = crypto_aead_ctx(aead);
	struct __packed { __be16 l; __be32 h; u16 len; } ltag;
	struct scatter_walk walk;
	u32 len = req->assoclen;
	u32 macp = 0;

	/* prepend the AAD with a length tag */
	if (len < 0xff00) {
		ltag.l = cpu_to_be16(len);
		ltag.len = 2;
	} else  {
		ltag.l = cpu_to_be16(0xfffe);
		put_unaligned_be32(len, &ltag.h);
		ltag.len = 6;
	}

	ccm_update_mac(ctx, mac, (u8 *)&ltag, ltag.len, &macp);
	scatterwalk_start(&walk, req->src);

	do {
		u32 n = scatterwalk_clamp(&walk, len);
		u8 *p;

		if (!n) {
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		}
		p = scatterwalk_map(&walk);
		ccm_update_mac(ctx, mac, p, n, &macp);
		len -= n;

		scatterwalk_unmap(p);
		scatterwalk_advance(&walk, n);
		scatterwalk_done(&walk, 0, len);
	} while (len);
}