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
struct isar_hw {int* buf; scalar_t__ iis; int clsb; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* write_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_HIS_VNR ; 
 scalar_t__ ISAR_IIS_VNR ; 
 int /*<<< orphan*/  ISAR_IRQBIT ; 
 int ISAR_MSG_HWVER ; 
 int /*<<< orphan*/  poll_mbox (struct isar_hw*,int) ; 
 int /*<<< orphan*/  send_mbox (struct isar_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ISARVersion(struct isar_hw *isar)
{
	int ver;

	/* disable ISAR IRQ */
	isar->write_reg(isar->hw, ISAR_IRQBIT, 0);
	isar->buf[0] = ISAR_MSG_HWVER;
	isar->buf[1] = 0;
	isar->buf[2] = 1;
	if (!send_mbox(isar, ISAR_HIS_VNR, 0, 3, NULL))
		return -1;
	if (!poll_mbox(isar, 1000))
		return -2;
	if (isar->iis == ISAR_IIS_VNR) {
		if (isar->clsb == 1) {
			ver = isar->buf[0] & 0xf;
			return ver;
		}
		return -3;
	}
	return -4;
}