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
struct skcipher_walk {int /*<<< orphan*/  alignmask; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  stride; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  flags; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  total; int /*<<< orphan*/  oiv; int /*<<< orphan*/  iv; scalar_t__ nbytes; } ;
struct TYPE_2__ {int flags; } ;
struct skcipher_request {TYPE_1__ base; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  SKCIPHER_WALK_SLEEP ; 
 int /*<<< orphan*/  crypto_skcipher_alignmask (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_blocksize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_skcipher_walksize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  scatterwalk_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int skcipher_walk_first (struct skcipher_walk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int skcipher_walk_skcipher(struct skcipher_walk *walk,
				  struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);

	walk->total = req->cryptlen;
	walk->nbytes = 0;
	walk->iv = req->iv;
	walk->oiv = req->iv;

	if (unlikely(!walk->total))
		return 0;

	scatterwalk_start(&walk->in, req->src);
	scatterwalk_start(&walk->out, req->dst);

	walk->flags &= ~SKCIPHER_WALK_SLEEP;
	walk->flags |= req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
		       SKCIPHER_WALK_SLEEP : 0;

	walk->blocksize = crypto_skcipher_blocksize(tfm);
	walk->stride = crypto_skcipher_walksize(tfm);
	walk->ivsize = crypto_skcipher_ivsize(tfm);
	walk->alignmask = crypto_skcipher_alignmask(tfm);

	return skcipher_walk_first(walk);
}