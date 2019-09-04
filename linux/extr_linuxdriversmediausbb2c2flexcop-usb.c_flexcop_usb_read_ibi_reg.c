#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ raw; } ;
typedef  TYPE_1__ flexcop_ibi_value ;
typedef  int /*<<< orphan*/  flexcop_ibi_register ;

/* Variables and functions */
 int /*<<< orphan*/  flexcop_usb_readwrite_dw (struct flexcop_device*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static flexcop_ibi_value flexcop_usb_read_ibi_reg(struct flexcop_device *fc,
	flexcop_ibi_register reg)
{
	flexcop_ibi_value val;
	val.raw = 0;
	flexcop_usb_readwrite_dw(fc, reg, &val.raw, 1);
	return val;
}