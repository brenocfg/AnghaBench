#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int* cache; } ;
struct hfi1_pportdata {TYPE_2__* dd; TYPE_1__ qsfp_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  hfi1_id; } ;

/* Variables and functions */
 size_t QSFP_EQ_INFO_OFFS ; 
 int /*<<< orphan*/  qsfp_write (struct hfi1_pportdata*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void apply_tx_eq_auto(struct hfi1_pportdata *ppd)
{
	u8 *cache = ppd->qsfp_info.cache;
	u8 tx_eq;

	if (!(cache[QSFP_EQ_INFO_OFFS] & 0x8))
		return;
	/* Disable adaptive TX EQ if present */
	tx_eq = cache[(128 * 3) + 241];
	tx_eq &= 0xF0;
	qsfp_write(ppd, ppd->dd->hfi1_id, (256 * 3) + 241, &tx_eq, 1);
}