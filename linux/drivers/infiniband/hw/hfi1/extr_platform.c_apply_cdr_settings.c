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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * cache; } ;
struct hfi1_pportdata {TYPE_2__* dd; TYPE_1__ qsfp_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  hfi1_id; } ;

/* Variables and functions */
 size_t QSFP_CDR_CTRL_BYTE_OFFS ; 
 int /*<<< orphan*/  apply_rx_cdr (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apply_tx_cdr (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsfp_write (struct hfi1_pportdata*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void apply_cdr_settings(
		struct hfi1_pportdata *ppd, u32 rx_preset_index,
		u32 tx_preset_index)
{
	u8 *cache = ppd->qsfp_info.cache;
	u8 cdr_ctrl_byte = cache[QSFP_CDR_CTRL_BYTE_OFFS];

	apply_rx_cdr(ppd, rx_preset_index, &cdr_ctrl_byte);

	apply_tx_cdr(ppd, tx_preset_index, &cdr_ctrl_byte);

	qsfp_write(ppd, ppd->dd->hfi1_id, QSFP_CDR_CTRL_BYTE_OFFS,
		   &cdr_ctrl_byte, 1);
}