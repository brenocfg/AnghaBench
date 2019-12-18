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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  scalar_t__ u8 ;
struct bfad_s {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int BFA_PREBOOT_BOOTLUN_MAX ; 
 int /*<<< orphan*/  bfa_iocfc_get_bootwwns (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 

int
bfad_get_linkup_delay(struct bfad_s *bfad)
{
	u8		nwwns = 0;
	wwn_t		wwns[BFA_PREBOOT_BOOTLUN_MAX];
	int		linkup_delay;

	/*
	 * Querying for the boot target port wwns
	 * -- read from boot information in flash.
	 * If nwwns > 0 => boot over SAN and set linkup_delay = 30
	 * else => local boot machine set linkup_delay = 0
	 */

	bfa_iocfc_get_bootwwns(&bfad->bfa, &nwwns, wwns);

	if (nwwns > 0)
		/* If Boot over SAN set linkup_delay = 30sec */
		linkup_delay = 30;
	else
		/* If local boot; no linkup_delay */
		linkup_delay = 0;

	return linkup_delay;
}