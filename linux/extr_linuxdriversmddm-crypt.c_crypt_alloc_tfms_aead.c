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
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tfms_aead; int /*<<< orphan*/  tfms; } ;
struct crypt_config {TYPE_1__ cipher_tfm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_free_tfms (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_alloc_tfms_aead(struct crypt_config *cc, char *ciphermode)
{
	int err;

	cc->cipher_tfm.tfms = kmalloc(sizeof(struct crypto_aead *), GFP_KERNEL);
	if (!cc->cipher_tfm.tfms)
		return -ENOMEM;

	cc->cipher_tfm.tfms_aead[0] = crypto_alloc_aead(ciphermode, 0, 0);
	if (IS_ERR(cc->cipher_tfm.tfms_aead[0])) {
		err = PTR_ERR(cc->cipher_tfm.tfms_aead[0]);
		crypt_free_tfms(cc);
		return err;
	}

	return 0;
}