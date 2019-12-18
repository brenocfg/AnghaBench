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
struct tg3 {int dummy; } ;

/* Variables and functions */
#define  ASIC_REV_5717 130 
#define  ASIC_REV_5719 129 
#define  ASIC_REV_5720 128 
 int CPMU_CLCK_ORIDE_MAC_ORIDE_EN ; 
 int /*<<< orphan*/  TG3_CPMU_CLCK_ORIDE ; 
 int /*<<< orphan*/  TG3_CPMU_CLCK_ORIDE_ENABLE ; 
 int TG3_CPMU_MAC_ORIDE_ENABLE ; 
 int tg3_asic_rev (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_restore_clk(struct tg3 *tp)
{
	u32 val;

	switch (tg3_asic_rev(tp)) {
	case ASIC_REV_5717:
		val = tr32(TG3_CPMU_CLCK_ORIDE_ENABLE);
		tw32(TG3_CPMU_CLCK_ORIDE_ENABLE,
		     val & ~TG3_CPMU_MAC_ORIDE_ENABLE);
		break;

	case ASIC_REV_5719:
	case ASIC_REV_5720:
		val = tr32(TG3_CPMU_CLCK_ORIDE);
		tw32(TG3_CPMU_CLCK_ORIDE, val & ~CPMU_CLCK_ORIDE_MAC_ORIDE_EN);
		break;

	default:
		return;
	}
}