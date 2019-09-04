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
typedef  int u32 ;
struct crypto_tfm {int cra_flags; } ;
struct crypto_spawn {int dummy; } ;
struct crypto_alg {int cra_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct crypto_tfm* ERR_CAST (struct crypto_tfm*) ; 
 struct crypto_tfm* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct crypto_tfm*) ; 
 struct crypto_tfm* __crypto_alloc_tfm (struct crypto_tfm*,int,int) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_tfm*) ; 
 struct crypto_tfm* crypto_spawn_alg (struct crypto_spawn*) ; 
 scalar_t__ unlikely (int) ; 

struct crypto_tfm *crypto_spawn_tfm(struct crypto_spawn *spawn, u32 type,
				    u32 mask)
{
	struct crypto_alg *alg;
	struct crypto_tfm *tfm;

	alg = crypto_spawn_alg(spawn);
	if (IS_ERR(alg))
		return ERR_CAST(alg);

	tfm = ERR_PTR(-EINVAL);
	if (unlikely((alg->cra_flags ^ type) & mask))
		goto out_put_alg;

	tfm = __crypto_alloc_tfm(alg, type, mask);
	if (IS_ERR(tfm))
		goto out_put_alg;

	return tfm;

out_put_alg:
	crypto_mod_put(alg);
	return tfm;
}