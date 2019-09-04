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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITVC_WRITE_DIR ; 
 int MCI_MEMORY_ADDRESS_BYTE0 ; 
 int MCI_MEMORY_ADDRESS_BYTE1 ; 
 int MCI_MEMORY_ADDRESS_BYTE2 ; 
 int MCI_MEMORY_DATA_BYTE0 ; 
 int MCI_MEMORY_DATA_BYTE1 ; 
 int MCI_MEMORY_DATA_BYTE2 ; 
 int MCI_MEMORY_DATA_BYTE3 ; 
 int MCI_MODE_MEMORY_WRITE ; 
 int set_itvc_reg (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_mci_complete (struct cx231xx*) ; 

__attribute__((used)) static int mc417_memory_write(struct cx231xx *dev, u32 address, u32 value)
{
	/*write data byte 0;*/

	u32 temp;
	int ret = 0;

	temp = 0x82 | MCI_MEMORY_DATA_BYTE0 | ((value & 0x000000FF) << 8);
	temp = temp << 10;
	ret = set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	if (ret < 0)
		return ret;
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/*write data byte 1;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE1 | (value & 0x0000FF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/*write data byte 2;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE2 | ((value & 0x00FF0000) >> 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/*write data byte 3;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE3 | ((value & 0xFF000000) >> 16);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/* write address byte 2;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE2 | MCI_MODE_MEMORY_WRITE |
		((address & 0x003F0000) >> 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/* write address byte 1;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/* write address byte 0;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_DIR, temp);

	/*wait for MIRDY line;*/
	wait_for_mci_complete(dev);

	return 0;
}