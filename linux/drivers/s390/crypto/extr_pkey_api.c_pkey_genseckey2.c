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
struct pkey_apqn {int card; int domain; } ;
typedef  enum pkey_key_type { ____Placeholder_pkey_key_type } pkey_key_type ;
typedef  enum pkey_key_size { ____Placeholder_pkey_key_size } pkey_key_size ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  PKEY_SIZE_AES_128 132 
#define  PKEY_SIZE_AES_192 131 
#define  PKEY_SIZE_AES_256 130 
#define  PKEY_TYPE_CCA_CIPHER 129 
#define  PKEY_TYPE_CCA_DATA 128 
 size_t SECKEYBLOBSIZE ; 
 int cca_gencipherkey (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int cca_genseckey (int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_genseckey2(const struct pkey_apqn *apqns, size_t nr_apqns,
			   enum pkey_key_type ktype, enum pkey_key_size ksize,
			   u32 kflags, u8 *keybuf, size_t *keybufsize)
{
	int i, card, dom, rc;

	/* check for at least one apqn given */
	if (!apqns || !nr_apqns)
		return -EINVAL;

	/* check key type and size */
	switch (ktype) {
	case PKEY_TYPE_CCA_DATA:
	case PKEY_TYPE_CCA_CIPHER:
		if (*keybufsize < SECKEYBLOBSIZE)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}
	switch (ksize) {
	case PKEY_SIZE_AES_128:
	case PKEY_SIZE_AES_192:
	case PKEY_SIZE_AES_256:
		break;
	default:
		return -EINVAL;
	}

	/* simple try all apqns from the list */
	for (i = 0, rc = -ENODEV; i < nr_apqns; i++) {
		card = apqns[i].card;
		dom = apqns[i].domain;
		if (ktype == PKEY_TYPE_CCA_DATA) {
			rc = cca_genseckey(card, dom, ksize, keybuf);
			*keybufsize = (rc ? 0 : SECKEYBLOBSIZE);
		} else /* TOKVER_CCA_VLSC */
			rc = cca_gencipherkey(card, dom, ksize, kflags,
					      keybuf, keybufsize);
		if (rc == 0)
			break;
	}

	return rc;
}