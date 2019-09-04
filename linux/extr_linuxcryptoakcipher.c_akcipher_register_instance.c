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
struct crypto_template {int dummy; } ;
struct akcipher_instance {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  akcipher_crypto_instance (struct akcipher_instance*) ; 
 int /*<<< orphan*/  akcipher_prepare_alg (int /*<<< orphan*/ *) ; 
 int crypto_register_instance (struct crypto_template*,int /*<<< orphan*/ ) ; 

int akcipher_register_instance(struct crypto_template *tmpl,
			       struct akcipher_instance *inst)
{
	akcipher_prepare_alg(&inst->alg);
	return crypto_register_instance(tmpl, akcipher_crypto_instance(inst));
}