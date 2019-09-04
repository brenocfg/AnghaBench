#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smca_bank {TYPE_1__* hwid; } ;
typedef  enum smca_bank_types { ____Placeholder_smca_bank_types } smca_bank_types ;
struct TYPE_2__ {int bank_type; } ;

/* Variables and functions */
 unsigned int MAX_NR_BANKS ; 
 int N_SMCA_BANK_TYPES ; 
 struct smca_bank* smca_banks ; 

__attribute__((used)) static enum smca_bank_types smca_get_bank_type(unsigned int bank)
{
	struct smca_bank *b;

	if (bank >= MAX_NR_BANKS)
		return N_SMCA_BANK_TYPES;

	b = &smca_banks[bank];
	if (!b->hwid)
		return N_SMCA_BANK_TYPES;

	return b->hwid->bank_type;
}