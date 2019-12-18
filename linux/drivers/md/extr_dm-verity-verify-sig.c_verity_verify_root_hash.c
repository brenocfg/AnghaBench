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

/* Variables and functions */
 scalar_t__ DM_VERITY_IS_SIG_FORCE_ENABLED () ; 
 int EINVAL ; 
 int ENOKEY ; 
 int /*<<< orphan*/  VERIFYING_UNSPECIFIED_SIGNATURE ; 
 int verify_pkcs7_signature (void const*,size_t,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int verity_verify_root_hash(const void *root_hash, size_t root_hash_len,
			    const void *sig_data, size_t sig_len)
{
	int ret;

	if (!root_hash || root_hash_len == 0)
		return -EINVAL;

	if (!sig_data  || sig_len == 0) {
		if (DM_VERITY_IS_SIG_FORCE_ENABLED())
			return -ENOKEY;
		else
			return 0;
	}

	ret = verify_pkcs7_signature(root_hash, root_hash_len, sig_data,
				sig_len, NULL, VERIFYING_UNSPECIFIED_SIGNATURE,
				NULL, NULL);

	return ret;
}