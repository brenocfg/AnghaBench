#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ;TYPE_3__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int Per_reset_sig; } ;
struct TYPE_10__ {int reset_block_000; int reset_block_100; int reset_block_200; int reset_block_300; int reset_block_400; int reset_block_500; int reset_block_600; int reset_block_700; int Block_reset_enable; int Special_controls; } ;
struct TYPE_12__ {TYPE_2__ misc_204; TYPE_1__ sw_reset_210; scalar_t__ raw; } ;
typedef  TYPE_3__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_208 ; 
 TYPE_3__ ibi_zero ; 
 int /*<<< orphan*/  misc_204 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  stub2 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 TYPE_3__ stub3 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  stub5 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  sw_reset_210 ; 

__attribute__((used)) static void flexcop_reset(struct flexcop_device *fc)
{
	flexcop_ibi_value v210, v204;

	/* reset the flexcop itself */
	fc->write_ibi_reg(fc,ctrl_208,ibi_zero);

	v210.raw = 0;
	v210.sw_reset_210.reset_block_000 = 1;
	v210.sw_reset_210.reset_block_100 = 1;
	v210.sw_reset_210.reset_block_200 = 1;
	v210.sw_reset_210.reset_block_300 = 1;
	v210.sw_reset_210.reset_block_400 = 1;
	v210.sw_reset_210.reset_block_500 = 1;
	v210.sw_reset_210.reset_block_600 = 1;
	v210.sw_reset_210.reset_block_700 = 1;
	v210.sw_reset_210.Block_reset_enable = 0xb2;
	v210.sw_reset_210.Special_controls = 0xc259;
	fc->write_ibi_reg(fc,sw_reset_210,v210);
	msleep(1);

	/* reset the periphical devices */

	v204 = fc->read_ibi_reg(fc,misc_204);
	v204.misc_204.Per_reset_sig = 0;
	fc->write_ibi_reg(fc,misc_204,v204);
	msleep(1);
	v204.misc_204.Per_reset_sig = 1;
	fc->write_ibi_reg(fc,misc_204,v204);
}