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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_REG_READ ; 
 int /*<<< orphan*/  vp7045_usb_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 

u8 vp7045_read_reg(struct dvb_usb_device *d, u8 reg)
{
	u8 obuf[2] = { 0 },v;
	obuf[1] = reg;

	vp7045_usb_op(d,TUNER_REG_READ,obuf,2,&v,1,30);

	return v;
}