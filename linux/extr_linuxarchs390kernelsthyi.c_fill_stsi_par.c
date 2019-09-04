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
struct sysinfo_2_2_2 {int /*<<< orphan*/  name; int /*<<< orphan*/  lpar_number; } ;
struct TYPE_2__ {int /*<<< orphan*/  infpval1; int /*<<< orphan*/  infppnam; int /*<<< orphan*/  infppnum; } ;
struct sthyi_sctns {TYPE_1__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAR_ID_VLD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stsi (struct sysinfo_2_2_2*,int,int,int) ; 

__attribute__((used)) static void fill_stsi_par(struct sthyi_sctns *sctns,
			  struct sysinfo_2_2_2 *sysinfo)
{
	if (stsi(sysinfo, 2, 2, 2))
		return;

	sctns->par.infppnum = sysinfo->lpar_number;
	memcpy(sctns->par.infppnam, sysinfo->name, sizeof(sctns->par.infppnam));

	sctns->par.infpval1 |= PAR_ID_VLD;
}