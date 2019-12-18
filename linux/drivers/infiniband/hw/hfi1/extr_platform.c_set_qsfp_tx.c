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
typedef  int u8 ;
struct hfi1_pportdata {TYPE_1__* dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  hfi1_id; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QSFP_TX_CTRL_BYTE_OFFS ; 
 int qsfp_write (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int set_qsfp_tx(struct hfi1_pportdata *ppd, int on)
{
	u8 tx_ctrl_byte = on ? 0x0 : 0xF;
	int ret = 0;

	ret = qsfp_write(ppd, ppd->dd->hfi1_id, QSFP_TX_CTRL_BYTE_OFFS,
			 &tx_ctrl_byte, 1);
	/* we expected 1, so consider 0 an error */
	if (ret == 0)
		ret = -EIO;
	else if (ret == 1)
		ret = 0;
	return ret;
}