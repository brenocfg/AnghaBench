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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_spawn {int /*<<< orphan*/  inst; int /*<<< orphan*/  frontend; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 int PTR_ERR (struct crypto_alg*) ; 
 struct crypto_alg* crypto_find_alg (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_init_spawn (struct crypto_spawn*,struct crypto_alg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 

int crypto_grab_spawn(struct crypto_spawn *spawn, const char *name,
		      u32 type, u32 mask)
{
	struct crypto_alg *alg;
	int err;

	alg = crypto_find_alg(name, spawn->frontend, type, mask);
	if (IS_ERR(alg))
		return PTR_ERR(alg);

	err = crypto_init_spawn(spawn, alg, spawn->inst, mask);
	crypto_mod_put(alg);
	return err;
}