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
struct jitterentropy {int /*<<< orphan*/  jent_lock; int /*<<< orphan*/ * entropy_collector; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct jitterentropy* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  jent_entropy_collector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jent_kcapi_cleanup(struct crypto_tfm *tfm)
{
	struct jitterentropy *rng = crypto_tfm_ctx(tfm);

	spin_lock(&rng->jent_lock);
	if (rng->entropy_collector)
		jent_entropy_collector_free(rng->entropy_collector);
	rng->entropy_collector = NULL;
	spin_unlock(&rng->jent_lock);
}