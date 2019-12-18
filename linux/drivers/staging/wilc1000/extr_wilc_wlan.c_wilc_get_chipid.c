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
typedef  int u32 ;
struct wilc {TYPE_1__* hif_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_read_reg ) (struct wilc*,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  is_wilc1000 (int) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct wilc*,int,int*) ; 

u32 wilc_get_chipid(struct wilc *wilc, bool update)
{
	static u32 chipid;
	u32 tempchipid = 0;
	u32 rfrevid = 0;

	if (chipid == 0 || update) {
		wilc->hif_func->hif_read_reg(wilc, 0x1000, &tempchipid);
		wilc->hif_func->hif_read_reg(wilc, 0x13f4, &rfrevid);
		if (!is_wilc1000(tempchipid)) {
			chipid = 0;
			return chipid;
		}
		if (tempchipid == 0x1002a0) {
			if (rfrevid != 0x1)
				tempchipid = 0x1002a1;
		} else if (tempchipid == 0x1002b0) {
			if (rfrevid == 0x4)
				tempchipid = 0x1002b1;
			else if (rfrevid != 0x3)
				tempchipid = 0x1002b2;
		}

		chipid = tempchipid;
	}
	return chipid;
}