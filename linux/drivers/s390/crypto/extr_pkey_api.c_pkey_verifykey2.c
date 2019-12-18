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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct secaeskeytoken {int /*<<< orphan*/  mkvp; scalar_t__ bitsize; } ;
struct pkey_apqn {int /*<<< orphan*/  domain; int /*<<< orphan*/  card; } ;
struct keytoken_header {scalar_t__ type; scalar_t__ version; } ;
struct cipherkeytoken {int wpllen; int /*<<< orphan*/  mkvp0; int /*<<< orphan*/  plfver; } ;
typedef  enum pkey_key_type { ____Placeholder_pkey_key_type } pkey_key_type ;
typedef  enum pkey_key_size { ____Placeholder_pkey_key_size } pkey_key_size ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PKEY_FLAGS_MATCH_ALT_MKVP ; 
 int /*<<< orphan*/  PKEY_FLAGS_MATCH_CUR_MKVP ; 
 int PKEY_SIZE_AES_128 ; 
 int PKEY_SIZE_AES_192 ; 
 int PKEY_SIZE_AES_256 ; 
 int PKEY_SIZE_UNKNOWN ; 
 int PKEY_TYPE_CCA_CIPHER ; 
 int PKEY_TYPE_CCA_DATA ; 
 scalar_t__ TOKTYPE_CCA_INTERNAL ; 
 scalar_t__ TOKVER_CCA_AES ; 
 scalar_t__ TOKVER_CCA_VLSC ; 
 int /*<<< orphan*/  ZCRYPT_CEX3C ; 
 int /*<<< orphan*/  ZCRYPT_CEX6 ; 
 int cca_check_secaescipherkey (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int cca_check_secaeskeytoken (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int cca_findcard2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_info ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_verifykey2(const u8 *key, size_t keylen,
			   u16 *cardnr, u16 *domain,
			   enum pkey_key_type *ktype,
			   enum pkey_key_size *ksize, u32 *flags)
{
	int rc;
	u32 _nr_apqns, *_apqns = NULL;
	struct keytoken_header *hdr = (struct keytoken_header *)key;

	if (keylen < sizeof(struct keytoken_header) ||
	    hdr->type != TOKTYPE_CCA_INTERNAL)
		return -EINVAL;

	if (hdr->version == TOKVER_CCA_AES) {
		struct secaeskeytoken *t = (struct secaeskeytoken *)key;

		rc = cca_check_secaeskeytoken(debug_info, 3, key, 0);
		if (rc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_CCA_DATA;
		if (ksize)
			*ksize = (enum pkey_key_size) t->bitsize;

		rc = cca_findcard2(&_apqns, &_nr_apqns, *cardnr, *domain,
				   ZCRYPT_CEX3C, t->mkvp, 0, 1);
		if (rc == 0 && flags)
			*flags = PKEY_FLAGS_MATCH_CUR_MKVP;
		if (rc == -ENODEV) {
			rc = cca_findcard2(&_apqns, &_nr_apqns,
					   *cardnr, *domain,
					   ZCRYPT_CEX3C, 0, t->mkvp, 1);
			if (rc == 0 && flags)
				*flags = PKEY_FLAGS_MATCH_ALT_MKVP;
		}
		if (rc)
			goto out;

		*cardnr = ((struct pkey_apqn *)_apqns)->card;
		*domain = ((struct pkey_apqn *)_apqns)->domain;

	} else if (hdr->version == TOKVER_CCA_VLSC) {
		struct cipherkeytoken *t = (struct cipherkeytoken *)key;

		rc = cca_check_secaescipherkey(debug_info, 3, key, 0, 1);
		if (rc)
			goto out;
		if (ktype)
			*ktype = PKEY_TYPE_CCA_CIPHER;
		if (ksize) {
			*ksize = PKEY_SIZE_UNKNOWN;
			if (!t->plfver && t->wpllen == 512)
				*ksize = PKEY_SIZE_AES_128;
			else if (!t->plfver && t->wpllen == 576)
				*ksize = PKEY_SIZE_AES_192;
			else if (!t->plfver && t->wpllen == 640)
				*ksize = PKEY_SIZE_AES_256;
		}

		rc = cca_findcard2(&_apqns, &_nr_apqns, *cardnr, *domain,
				   ZCRYPT_CEX6, t->mkvp0, 0, 1);
		if (rc == 0 && flags)
			*flags = PKEY_FLAGS_MATCH_CUR_MKVP;
		if (rc == -ENODEV) {
			rc = cca_findcard2(&_apqns, &_nr_apqns,
					   *cardnr, *domain,
					   ZCRYPT_CEX6, 0, t->mkvp0, 1);
			if (rc == 0 && flags)
				*flags = PKEY_FLAGS_MATCH_ALT_MKVP;
		}
		if (rc)
			goto out;

		*cardnr = ((struct pkey_apqn *)_apqns)->card;
		*domain = ((struct pkey_apqn *)_apqns)->domain;

	} else
		rc = -EINVAL;

out:
	kfree(_apqns);
	return rc;
}