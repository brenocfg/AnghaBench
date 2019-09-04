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
struct crypto_type {int type; int maskset; } ;
struct crypto_spawn {struct crypto_type const* frontend; } ;
struct crypto_instance {int dummy; } ;
struct crypto_alg {int cra_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int crypto_init_spawn (struct crypto_spawn*,struct crypto_alg*,struct crypto_instance*,int) ; 

int crypto_init_spawn2(struct crypto_spawn *spawn, struct crypto_alg *alg,
		       struct crypto_instance *inst,
		       const struct crypto_type *frontend)
{
	int err = -EINVAL;

	if ((alg->cra_flags ^ frontend->type) & frontend->maskset)
		goto out;

	spawn->frontend = frontend;
	err = crypto_init_spawn(spawn, alg, inst, frontend->maskset);

out:
	return err;
}