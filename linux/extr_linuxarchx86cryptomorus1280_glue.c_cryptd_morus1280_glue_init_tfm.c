#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct cryptd_aead {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {char* cra_driver_name; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_INTERNAL ; 
 int CRYPTO_MAX_ALG_NAME ; 
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct cryptd_aead*) ; 
 int PTR_ERR (struct cryptd_aead*) ; 
 struct cryptd_aead* cryptd_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* crypto_aead_alg (struct crypto_aead*) ; 
 struct cryptd_aead** crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_reqsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*) ; 

int cryptd_morus1280_glue_init_tfm(struct crypto_aead *aead)
{
	struct cryptd_aead *cryptd_tfm;
	struct cryptd_aead **ctx = crypto_aead_ctx(aead);
	const char *name = crypto_aead_alg(aead)->base.cra_driver_name;
	char internal_name[CRYPTO_MAX_ALG_NAME];

	if (snprintf(internal_name, CRYPTO_MAX_ALG_NAME, "__%s", name)
			>= CRYPTO_MAX_ALG_NAME)
		return -ENAMETOOLONG;

	cryptd_tfm = cryptd_alloc_aead(internal_name, CRYPTO_ALG_INTERNAL,
				       CRYPTO_ALG_INTERNAL);
	if (IS_ERR(cryptd_tfm))
		return PTR_ERR(cryptd_tfm);

	*ctx = cryptd_tfm;
	crypto_aead_set_reqsize(aead, crypto_aead_reqsize(&cryptd_tfm->base));
	return 0;
}