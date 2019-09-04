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
typedef  int u32 ;
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int smi_read (int) ; 
 int /*<<< orphan*/  smi_write (int,int) ; 

__attribute__((used)) static void smi_i2c_cfg(struct smi_dev *dev, u32 sw_ctl)
{
	u32 dwCtrl;

	dwCtrl = smi_read(sw_ctl);
	dwCtrl &= ~0x18; /* disable output.*/
	dwCtrl |= 0x21; /* reset and software mode.*/
	dwCtrl &= ~0xff00;
	dwCtrl |= 0x6400;
	smi_write(sw_ctl, dwCtrl);
	msleep(20);
	dwCtrl = smi_read(sw_ctl);
	dwCtrl &= ~0x20;
	smi_write(sw_ctl, dwCtrl);
}