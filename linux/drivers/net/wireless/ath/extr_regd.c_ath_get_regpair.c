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
struct reg_dmn_pair_mapping {int reg_domain; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_dmn_pair_mapping*) ; 
 int NO_ENUMRD ; 
 struct reg_dmn_pair_mapping* regDomainPairs ; 

__attribute__((used)) static struct reg_dmn_pair_mapping*
ath_get_regpair(int regdmn)
{
	int i;

	if (regdmn == NO_ENUMRD)
		return NULL;
	for (i = 0; i < ARRAY_SIZE(regDomainPairs); i++) {
		if (regDomainPairs[i].reg_domain == regdmn)
			return &regDomainPairs[i];
	}
	return NULL;
}