#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; unsigned int total; TYPE_4__ src; TYPE_2__ dst; int /*<<< orphan*/  stride; int /*<<< orphan*/  iv; } ;
struct skcipher_request {scalar_t__ cryptlen; } ;
struct crypto_skcipher {int dummy; } ;
struct chacha20_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHACHA20_BLOCK_SIZE ; 
 int /*<<< orphan*/  chacha20_doneon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int crypto_chacha20_crypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_chacha20_init (int /*<<< orphan*/ *,struct chacha20_ctx*,int /*<<< orphan*/ ) ; 
 struct chacha20_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  may_use_simd () ; 
 unsigned int round_down (unsigned int,int /*<<< orphan*/ ) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int chacha20_neon(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct chacha20_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_walk walk;
	u32 state[16];
	int err;

	if (req->cryptlen <= CHACHA20_BLOCK_SIZE || !may_use_simd())
		return crypto_chacha20_crypt(req);

	err = skcipher_walk_virt(&walk, req, true);

	crypto_chacha20_init(state, ctx, walk.iv);

	kernel_neon_begin();
	while (walk.nbytes > 0) {
		unsigned int nbytes = walk.nbytes;

		if (nbytes < walk.total)
			nbytes = round_down(nbytes, walk.stride);

		chacha20_doneon(state, walk.dst.virt.addr, walk.src.virt.addr,
				nbytes);
		err = skcipher_walk_done(&walk, walk.nbytes - nbytes);
	}
	kernel_neon_end();

	return err;
}