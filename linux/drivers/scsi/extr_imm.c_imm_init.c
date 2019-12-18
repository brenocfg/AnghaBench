#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int EIO ; 
 int device_check (TYPE_1__*) ; 
 int imm_connect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  imm_reset_pulse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int imm_init(imm_struct *dev)
{
	if (imm_connect(dev, 0) != 1)
		return -EIO;
	imm_reset_pulse(dev->base);
	mdelay(1);	/* Delay to allow devices to settle */
	imm_disconnect(dev);
	mdelay(1);	/* Another delay to allow devices to settle */
	return device_check(dev);
}