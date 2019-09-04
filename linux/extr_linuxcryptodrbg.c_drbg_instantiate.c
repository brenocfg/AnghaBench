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
struct drbg_string {int dummy; } ;
struct drbg_state {int pr; int seeded; int /*<<< orphan*/  drbg_mutex; int /*<<< orphan*/ * jent; int /*<<< orphan*/  reseed_threshold; int /*<<< orphan*/ * core; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int drbg_alloc_state (struct drbg_state*) ; 
 int /*<<< orphan*/ * drbg_cores ; 
 int /*<<< orphan*/  drbg_max_requests (struct drbg_state*) ; 
 int drbg_prepare_hrng (struct drbg_state*) ; 
 int drbg_seed (struct drbg_state*,struct drbg_string*,int) ; 
 int /*<<< orphan*/  drbg_uninstantiate (struct drbg_state*) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,int,char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int drbg_instantiate(struct drbg_state *drbg, struct drbg_string *pers,
			    int coreref, bool pr)
{
	int ret;
	bool reseed = true;

	pr_devel("DRBG: Initializing DRBG core %d with prediction resistance "
		 "%s\n", coreref, pr ? "enabled" : "disabled");
	mutex_lock(&drbg->drbg_mutex);

	/* 9.1 step 1 is implicit with the selected DRBG type */

	/*
	 * 9.1 step 2 is implicit as caller can select prediction resistance
	 * and the flag is copied into drbg->flags --
	 * all DRBG types support prediction resistance
	 */

	/* 9.1 step 4 is implicit in  drbg_sec_strength */

	if (!drbg->core) {
		drbg->core = &drbg_cores[coreref];
		drbg->pr = pr;
		drbg->seeded = false;
		drbg->reseed_threshold = drbg_max_requests(drbg);

		ret = drbg_alloc_state(drbg);
		if (ret)
			goto unlock;

		ret = drbg_prepare_hrng(drbg);
		if (ret)
			goto free_everything;

		if (IS_ERR(drbg->jent)) {
			ret = PTR_ERR(drbg->jent);
			drbg->jent = NULL;
			if (fips_enabled || ret != -ENOENT)
				goto free_everything;
			pr_info("DRBG: Continuing without Jitter RNG\n");
		}

		reseed = false;
	}

	ret = drbg_seed(drbg, pers, reseed);

	if (ret && !reseed)
		goto free_everything;

	mutex_unlock(&drbg->drbg_mutex);
	return ret;

unlock:
	mutex_unlock(&drbg->drbg_mutex);
	return ret;

free_everything:
	mutex_unlock(&drbg->drbg_mutex);
	drbg_uninstantiate(drbg);
	return ret;
}