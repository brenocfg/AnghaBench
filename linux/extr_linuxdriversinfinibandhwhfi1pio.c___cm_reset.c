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
typedef  int u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_CTRL ; 
 int SEND_CTRL_CM_RESET_SMASK ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

void __cm_reset(struct hfi1_devdata *dd, u64 sendctrl)
{
	write_csr(dd, SEND_CTRL, sendctrl | SEND_CTRL_CM_RESET_SMASK);
	while (1) {
		udelay(1);
		sendctrl = read_csr(dd, SEND_CTRL);
		if ((sendctrl & SEND_CTRL_CM_RESET_SMASK) == 0)
			break;
	}
}