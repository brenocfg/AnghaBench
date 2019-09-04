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
struct drbg_string {int dummy; } ;
struct drbg_state {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 struct drbg_state* crypto_rng_ctx (struct crypto_rng*) ; 
 struct crypto_tfm* crypto_rng_tfm (struct crypto_rng*) ; 
 int /*<<< orphan*/  crypto_tfm_alg_driver_name (struct crypto_tfm*) ; 
 int /*<<< orphan*/  drbg_convert_tfm_core (int /*<<< orphan*/ ,int*,int*) ; 
 int drbg_instantiate (struct drbg_state*,struct drbg_string*,int,int) ; 
 int /*<<< orphan*/  drbg_string_fill (struct drbg_string*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int drbg_kcapi_seed(struct crypto_rng *tfm,
			   const u8 *seed, unsigned int slen)
{
	struct drbg_state *drbg = crypto_rng_ctx(tfm);
	struct crypto_tfm *tfm_base = crypto_rng_tfm(tfm);
	bool pr = false;
	struct drbg_string string;
	struct drbg_string *seed_string = NULL;
	int coreref = 0;

	drbg_convert_tfm_core(crypto_tfm_alg_driver_name(tfm_base), &coreref,
			      &pr);
	if (0 < slen) {
		drbg_string_fill(&string, seed, slen);
		seed_string = &string;
	}

	return drbg_instantiate(drbg, seed_string, coreref, pr);
}