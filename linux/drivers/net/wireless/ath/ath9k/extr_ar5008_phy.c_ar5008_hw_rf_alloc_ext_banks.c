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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ia_rows; } ;
struct ath_hw {int /*<<< orphan*/  analogBank6Data; int /*<<< orphan*/  dev; TYPE_1__ iniBank6; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5008_hw_rf_alloc_ext_banks(struct ath_hw *ah)
{
	int size = ah->iniBank6.ia_rows * sizeof(u32);

	if (AR_SREV_9280_20_OR_LATER(ah))
	    return 0;

	ah->analogBank6Data = devm_kzalloc(ah->dev, size, GFP_KERNEL);
	if (!ah->analogBank6Data)
		return -ENOMEM;

	return 0;
}