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
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {int /*<<< orphan*/ * Log2PhyMap; int /*<<< orphan*/ * Phy2LogMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms_lib_free_logicalmap(struct us_data *us)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	kfree(info->MS_Lib.Phy2LogMap);
	info->MS_Lib.Phy2LogMap = NULL;

	kfree(info->MS_Lib.Log2PhyMap);
	info->MS_Lib.Log2PhyMap = NULL;

	return 0;
}