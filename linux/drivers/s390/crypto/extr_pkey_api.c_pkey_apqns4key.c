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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct secaeskeytoken {int /*<<< orphan*/  mkvp; } ;
struct pkey_apqn {int dummy; } ;
struct keytoken_header {scalar_t__ type; scalar_t__ version; } ;
struct cipherkeytoken {int /*<<< orphan*/  mkvp0; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ PKEY_FLAGS_MATCH_ALT_MKVP ; 
 scalar_t__ PKEY_FLAGS_MATCH_CUR_MKVP ; 
 scalar_t__ TOKTYPE_CCA_INTERNAL ; 
 scalar_t__ TOKVER_CCA_AES ; 
 scalar_t__ TOKVER_CCA_VLSC ; 
 int ZCRYPT_CEX3C ; 
 int ZCRYPT_CEX6 ; 
 int cca_findcard2 (scalar_t__**,scalar_t__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (struct pkey_apqn*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int pkey_apqns4key(const u8 *key, size_t keylen, u32 flags,
			  struct pkey_apqn *apqns, size_t *nr_apqns)
{
	int rc = EINVAL;
	u32 _nr_apqns, *_apqns = NULL;
	struct keytoken_header *hdr = (struct keytoken_header *)key;

	if (keylen < sizeof(struct keytoken_header) ||
	    hdr->type != TOKTYPE_CCA_INTERNAL ||
	    flags == 0)
		return -EINVAL;

	if (hdr->version == TOKVER_CCA_AES || hdr->version == TOKVER_CCA_VLSC) {
		int minhwtype = ZCRYPT_CEX3C;
		u64 cur_mkvp = 0, old_mkvp = 0;

		if (hdr->version == TOKVER_CCA_AES) {
			struct secaeskeytoken *t = (struct secaeskeytoken *)key;

			if (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
				cur_mkvp = t->mkvp;
			if (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
				old_mkvp = t->mkvp;
		} else {
			struct cipherkeytoken *t = (struct cipherkeytoken *)key;

			minhwtype = ZCRYPT_CEX6;
			if (flags & PKEY_FLAGS_MATCH_CUR_MKVP)
				cur_mkvp = t->mkvp0;
			if (flags & PKEY_FLAGS_MATCH_ALT_MKVP)
				old_mkvp = t->mkvp0;
		}
		rc = cca_findcard2(&_apqns, &_nr_apqns, 0xFFFF, 0xFFFF,
				   minhwtype, cur_mkvp, old_mkvp, 1);
		if (rc)
			goto out;
		if (apqns) {
			if (*nr_apqns < _nr_apqns)
				rc = -ENOSPC;
			else
				memcpy(apqns, _apqns, _nr_apqns * sizeof(u32));
		}
		*nr_apqns = _nr_apqns;
	}

out:
	kfree(_apqns);
	return rc;
}