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
typedef  int u32 ;
struct tg3 {int pci_fn; } ;

/* Variables and functions */
 int APE_LOCK_GRANT_DRIVER ; 
 scalar_t__ ASIC_REV_5761 ; 
 int /*<<< orphan*/  ENABLE_APE ; 
#define  TG3_APE_LOCK_GPIO 134 
 int TG3_APE_LOCK_GRANT ; 
#define  TG3_APE_LOCK_GRC 133 
#define  TG3_APE_LOCK_MEM 132 
#define  TG3_APE_LOCK_PHY0 131 
#define  TG3_APE_LOCK_PHY1 130 
#define  TG3_APE_LOCK_PHY2 129 
#define  TG3_APE_LOCK_PHY3 128 
 int TG3_APE_PER_LOCK_GRANT ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int,int) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_ape_unlock(struct tg3 *tp, int locknum)
{
	u32 gnt, bit;

	if (!tg3_flag(tp, ENABLE_APE))
		return;

	switch (locknum) {
	case TG3_APE_LOCK_GPIO:
		if (tg3_asic_rev(tp) == ASIC_REV_5761)
			return;
		/* fall through */
	case TG3_APE_LOCK_GRC:
	case TG3_APE_LOCK_MEM:
		if (!tp->pci_fn)
			bit = APE_LOCK_GRANT_DRIVER;
		else
			bit = 1 << tp->pci_fn;
		break;
	case TG3_APE_LOCK_PHY0:
	case TG3_APE_LOCK_PHY1:
	case TG3_APE_LOCK_PHY2:
	case TG3_APE_LOCK_PHY3:
		bit = APE_LOCK_GRANT_DRIVER;
		break;
	default:
		return;
	}

	if (tg3_asic_rev(tp) == ASIC_REV_5761)
		gnt = TG3_APE_LOCK_GRANT;
	else
		gnt = TG3_APE_PER_LOCK_GRANT;

	tg3_ape_write32(tp, gnt + 4 * locknum, bit);
}