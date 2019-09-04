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
struct crypto_larval {int /*<<< orphan*/  alg; struct crypto_alg* adult; int /*<<< orphan*/  completion; } ;
struct crypto_alg {int cra_flags; } ;

/* Variables and functions */
 int CRYPTO_ALG_TESTED ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOENT ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ crypto_is_test_larval (struct crypto_larval*) ; 
 int /*<<< orphan*/  crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (int /*<<< orphan*/ *) ; 
 long wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct crypto_alg *crypto_larval_wait(struct crypto_alg *alg)
{
	struct crypto_larval *larval = (void *)alg;
	long timeout;

	timeout = wait_for_completion_killable_timeout(
		&larval->completion, 60 * HZ);

	alg = larval->adult;
	if (timeout < 0)
		alg = ERR_PTR(-EINTR);
	else if (!timeout)
		alg = ERR_PTR(-ETIMEDOUT);
	else if (!alg)
		alg = ERR_PTR(-ENOENT);
	else if (crypto_is_test_larval(larval) &&
		 !(alg->cra_flags & CRYPTO_ALG_TESTED))
		alg = ERR_PTR(-EAGAIN);
	else if (!crypto_mod_get(alg))
		alg = ERR_PTR(-EAGAIN);
	crypto_mod_put(&larval->alg);

	return alg;
}