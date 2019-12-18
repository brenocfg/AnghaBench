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
struct TYPE_2__ {scalar_t__ NumberOfLogBlock; scalar_t__ NumberOfPhyBlock; scalar_t__ PagesPerBlock; scalar_t__ blockSize; scalar_t__ cardType; scalar_t__ SectorsPerCylinder; scalar_t__ BytesPerSector; scalar_t__ flags; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  ms_lib_free_logicalmap (struct us_data*) ; 
 int /*<<< orphan*/  ms_lib_free_writebuf (struct us_data*) ; 

__attribute__((used)) static void ms_lib_free_allocatedarea(struct us_data *us)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	ms_lib_free_writebuf(us); /* Free MS_Lib.pagemap */
	ms_lib_free_logicalmap(us); /* kfree MS_Lib.Phy2LogMap and MS_Lib.Log2PhyMap */

	/* set struct us point flag to 0 */
	info->MS_Lib.flags = 0;
	info->MS_Lib.BytesPerSector = 0;
	info->MS_Lib.SectorsPerCylinder = 0;

	info->MS_Lib.cardType = 0;
	info->MS_Lib.blockSize = 0;
	info->MS_Lib.PagesPerBlock = 0;

	info->MS_Lib.NumberOfPhyBlock = 0;
	info->MS_Lib.NumberOfLogBlock = 0;
}