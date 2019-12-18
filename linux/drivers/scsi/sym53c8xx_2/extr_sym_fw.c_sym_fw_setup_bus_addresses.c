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
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u32 ;
struct sym_hcb {scalar_t__ scriptz_ba; int /*<<< orphan*/  fwz_bas; scalar_t__ scriptb_ba; int /*<<< orphan*/  fwb_bas; scalar_t__ scripta_ba; int /*<<< orphan*/  fwa_bas; } ;
struct sym_fw {scalar_t__ z_ofs; scalar_t__ b_ofs; scalar_t__ a_ofs; } ;

/* Variables and functions */

__attribute__((used)) static void 
sym_fw_setup_bus_addresses(struct sym_hcb *np, struct sym_fw *fw)
{
	u32 *pa;
	u_short *po;
	int i;

	/*
	 *  Build the bus address table for script A 
	 *  from the script A offset table.
	 */
	po = (u_short *) fw->a_ofs;
	pa = (u32 *) &np->fwa_bas;
	for (i = 0 ; i < sizeof(np->fwa_bas)/sizeof(u32) ; i++)
		pa[i] = np->scripta_ba + po[i];

	/*
	 *  Same for script B.
	 */
	po = (u_short *) fw->b_ofs;
	pa = (u32 *) &np->fwb_bas;
	for (i = 0 ; i < sizeof(np->fwb_bas)/sizeof(u32) ; i++)
		pa[i] = np->scriptb_ba + po[i];

	/*
	 *  Same for script Z.
	 */
	po = (u_short *) fw->z_ofs;
	pa = (u32 *) &np->fwz_bas;
	for (i = 0 ; i < sizeof(np->fwz_bas)/sizeof(u32) ; i++)
		pa[i] = np->scriptz_ba + po[i];
}