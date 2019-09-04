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
struct jitterentropy {int /*<<< orphan*/  jent_lock; int /*<<< orphan*/  entropy_collector; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct jitterentropy* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  jent_entropy_collector_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jent_kcapi_init(struct crypto_tfm *tfm)
{
	struct jitterentropy *rng = crypto_tfm_ctx(tfm);
	int ret = 0;

	rng->entropy_collector = jent_entropy_collector_alloc(1, 0);
	if (!rng->entropy_collector)
		ret = -ENOMEM;

	spin_lock_init(&rng->jent_lock);
	return ret;
}