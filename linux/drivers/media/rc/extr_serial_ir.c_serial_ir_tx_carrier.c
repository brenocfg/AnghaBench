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
typedef  int u32 ;
struct rc_dev {int dummy; } ;
struct TYPE_2__ {int carrier; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ serial_ir ; 

__attribute__((used)) static int serial_ir_tx_carrier(struct rc_dev *dev, u32 carrier)
{
	if (carrier > 500000 || carrier < 20000)
		return -EINVAL;

	serial_ir.carrier = carrier;
	return 0;
}