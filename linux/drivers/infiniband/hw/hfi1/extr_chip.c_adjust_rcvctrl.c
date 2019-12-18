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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int /*<<< orphan*/  rcvctrl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_CTRL ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adjust_rcvctrl(struct hfi1_devdata *dd, u64 add, u64 clear)
{
	u64 rcvctrl;
	unsigned long flags;

	spin_lock_irqsave(&dd->rcvctrl_lock, flags);
	rcvctrl = read_csr(dd, RCV_CTRL);
	rcvctrl |= add;
	rcvctrl &= ~clear;
	write_csr(dd, RCV_CTRL, rcvctrl);
	spin_unlock_irqrestore(&dd->rcvctrl_lock, flags);
}