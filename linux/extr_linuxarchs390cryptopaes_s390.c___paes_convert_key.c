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
struct pkey_seckey {int dummy; } ;
struct pkey_protkey {int dummy; } ;

/* Variables and functions */
 int pkey_skey2pkey (struct pkey_seckey*,struct pkey_protkey*) ; 

__attribute__((used)) static inline int __paes_convert_key(struct pkey_seckey *sk,
				     struct pkey_protkey *pk)
{
	int i, ret;

	/* try three times in case of failure */
	for (i = 0; i < 3; i++) {
		ret = pkey_skey2pkey(sk, pk);
		if (ret == 0)
			break;
	}

	return ret;
}