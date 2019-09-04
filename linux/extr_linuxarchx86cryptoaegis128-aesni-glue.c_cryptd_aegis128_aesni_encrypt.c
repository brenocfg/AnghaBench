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
struct crypto_aead {int dummy; } ;
struct cryptd_aead {struct crypto_aead base; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 
 struct crypto_aead* cryptd_aead_child (struct cryptd_aead*) ; 
 int /*<<< orphan*/  cryptd_aead_queued (struct cryptd_aead*) ; 
 struct cryptd_aead** crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  in_atomic () ; 
 scalar_t__ irq_fpu_usable () ; 

__attribute__((used)) static int cryptd_aegis128_aesni_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct cryptd_aead **ctx = crypto_aead_ctx(aead);
	struct cryptd_aead *cryptd_tfm = *ctx;

	aead = &cryptd_tfm->base;
	if (irq_fpu_usable() && (!in_atomic() ||
				 !cryptd_aead_queued(cryptd_tfm)))
		aead = cryptd_aead_child(cryptd_tfm);

	aead_request_set_tfm(req, aead);

	return crypto_aead_encrypt(req);
}