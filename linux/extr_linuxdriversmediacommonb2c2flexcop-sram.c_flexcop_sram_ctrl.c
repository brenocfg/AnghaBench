#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ;TYPE_2__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int ctrl_usb_wan; int ctrl_sramdma; int ctrl_maximumfill; } ;
struct TYPE_6__ {TYPE_1__ sram_dest_reg_714; } ;
typedef  TYPE_2__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  sram_dest_reg_714 ; 
 TYPE_2__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 

void flexcop_sram_ctrl(struct flexcop_device *fc, int usb_wan, int sramdma, int maximumfill)
{
	flexcop_ibi_value v = fc->read_ibi_reg(fc,sram_dest_reg_714);
	v.sram_dest_reg_714.ctrl_usb_wan = usb_wan;
	v.sram_dest_reg_714.ctrl_sramdma = sramdma;
	v.sram_dest_reg_714.ctrl_maximumfill = maximumfill;
	fc->write_ibi_reg(fc,sram_dest_reg_714,v);
}