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
typedef  int u8 ;
struct matrox_device {int data_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MATROX_GET_CONTROL ; 
 int /*<<< orphan*/  MATROX_GET_DATA ; 
 int matrox_w1_read_reg (struct matrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrox_w1_write_reg (struct matrox_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void matrox_w1_write_ddc_bit(void *data, u8 bit)
{
	u8 ret;
	struct matrox_device *dev = data;

	if (bit)
		bit = 0;
	else
		bit = dev->data_mask;

	ret = matrox_w1_read_reg(dev, MATROX_GET_CONTROL);
	matrox_w1_write_reg(dev, MATROX_GET_CONTROL, ((ret & ~dev->data_mask) | bit));
	matrox_w1_write_reg(dev, MATROX_GET_DATA, 0x00);
}