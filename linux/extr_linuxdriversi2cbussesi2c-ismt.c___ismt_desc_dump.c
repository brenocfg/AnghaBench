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
struct ismt_desc {struct ismt_desc const* dptr_high; struct ismt_desc const* dptr_low; struct ismt_desc const* txbytes; struct ismt_desc const* rxbytes; struct ismt_desc const* retry; struct ismt_desc const* status; struct ismt_desc const* control; struct ismt_desc const* rd_len; struct ismt_desc const* wr_len_cmd; struct ismt_desc const* tgtaddr_rw; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct ismt_desc const*) ; 

__attribute__((used)) static void __ismt_desc_dump(struct device *dev, const struct ismt_desc *desc)
{

	dev_dbg(dev, "Descriptor struct:  %p\n", desc);
	dev_dbg(dev, "\ttgtaddr_rw=0x%02X\n", desc->tgtaddr_rw);
	dev_dbg(dev, "\twr_len_cmd=0x%02X\n", desc->wr_len_cmd);
	dev_dbg(dev, "\trd_len=    0x%02X\n", desc->rd_len);
	dev_dbg(dev, "\tcontrol=   0x%02X\n", desc->control);
	dev_dbg(dev, "\tstatus=    0x%02X\n", desc->status);
	dev_dbg(dev, "\tretry=     0x%02X\n", desc->retry);
	dev_dbg(dev, "\trxbytes=   0x%02X\n", desc->rxbytes);
	dev_dbg(dev, "\ttxbytes=   0x%02X\n", desc->txbytes);
	dev_dbg(dev, "\tdptr_low=  0x%08X\n", desc->dptr_low);
	dev_dbg(dev, "\tdptr_high= 0x%08X\n", desc->dptr_high);
}