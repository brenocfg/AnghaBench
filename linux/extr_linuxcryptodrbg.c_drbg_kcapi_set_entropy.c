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
struct drbg_state {int /*<<< orphan*/  drbg_mutex; int /*<<< orphan*/  test_data; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 struct drbg_state* crypto_rng_ctx (struct crypto_rng*) ; 
 int /*<<< orphan*/  drbg_string_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbg_kcapi_set_entropy(struct crypto_rng *tfm,
				   const u8 *data, unsigned int len)
{
	struct drbg_state *drbg = crypto_rng_ctx(tfm);

	mutex_lock(&drbg->drbg_mutex);
	drbg_string_fill(&drbg->test_data, data, len);
	mutex_unlock(&drbg->drbg_mutex);
}