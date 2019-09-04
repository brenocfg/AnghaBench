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
typedef  int u8 ;
struct mce_bank {unsigned long long ctl; int init; } ;
struct TYPE_2__ {int banks; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mce_bank* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ mca_cfg ; 
 struct mce_bank* mce_banks ; 

__attribute__((used)) static int __mcheck_cpu_mce_banks_init(void)
{
	int i;
	u8 num_banks = mca_cfg.banks;

	mce_banks = kcalloc(num_banks, sizeof(struct mce_bank), GFP_KERNEL);
	if (!mce_banks)
		return -ENOMEM;

	for (i = 0; i < num_banks; i++) {
		struct mce_bank *b = &mce_banks[i];

		b->ctl = -1ULL;
		b->init = 1;
	}
	return 0;
}