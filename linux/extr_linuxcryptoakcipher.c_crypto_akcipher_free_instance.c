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
struct crypto_instance {int dummy; } ;
struct akcipher_instance {int /*<<< orphan*/  (* free ) (struct akcipher_instance*) ;} ;

/* Variables and functions */
 struct akcipher_instance* akcipher_instance (struct crypto_instance*) ; 
 int /*<<< orphan*/  stub1 (struct akcipher_instance*) ; 

__attribute__((used)) static void crypto_akcipher_free_instance(struct crypto_instance *inst)
{
	struct akcipher_instance *akcipher = akcipher_instance(inst);

	akcipher->free(akcipher);
}