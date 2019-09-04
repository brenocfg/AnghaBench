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
struct camera_data {int dummy; } ;

/* Variables and functions */

void cpia2_dbg_dump_registers(struct camera_data *cam)
{
#ifdef _CPIA2_DEBUG_
	struct cpia2_command cmd;

	if (!(debugs_on & DEBUG_DUMP_REGS))
		return;

	cmd.direction = TRANSFER_READ;

	/* Start with bank 0 (SYSTEM) */
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
	cmd.reg_count = 3;
	cmd.start = 0;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "System Device Hi      = 0x%X\n",
	       cmd.buffer.block_data[0]);
	printk(KERN_DEBUG "System Device Lo      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	printk(KERN_DEBUG "System_system control = 0x%X\n",
	       cmd.buffer.block_data[2]);

	/* Bank 1 (VC) */
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
	cmd.reg_count = 4;
	cmd.start = 0x80;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "ASIC_ID       = 0x%X\n",
	       cmd.buffer.block_data[0]);
	printk(KERN_DEBUG "ASIC_REV      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	printk(KERN_DEBUG "PW_CONTRL     = 0x%X\n",
	       cmd.buffer.block_data[2]);
	printk(KERN_DEBUG "WAKEUP        = 0x%X\n",
	       cmd.buffer.block_data[3]);

	cmd.start = 0xA0;	/* ST_CTRL */
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "Stream ctrl   = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xA4;	/* Stream status */
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "Stream status = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xA8;	/* USB status */
	cmd.reg_count = 3;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "USB_CTRL      = 0x%X\n",
	       cmd.buffer.block_data[0]);
	printk(KERN_DEBUG "USB_STRM      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	printk(KERN_DEBUG "USB_STATUS    = 0x%X\n",
	       cmd.buffer.block_data[2]);

	cmd.start = 0xAF;	/* USB settings */
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "USB settings  = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xC0;	/* VC stuff */
	cmd.reg_count = 26;
	cpia2_send_command(cam, &cmd);
	printk(KERN_DEBUG "VC Control    = 0x%0X\n",
	       cmd.buffer.block_data[0]);
	printk(KERN_DEBUG "VC Format     = 0x%0X\n",
	       cmd.buffer.block_data[3]);
	printk(KERN_DEBUG "VC Clocks     = 0x%0X\n",
	       cmd.buffer.block_data[4]);
	printk(KERN_DEBUG "VC IHSize     = 0x%0X\n",
	       cmd.buffer.block_data[5]);
	printk(KERN_DEBUG "VC Xlim Hi    = 0x%0X\n",
	       cmd.buffer.block_data[6]);
	printk(KERN_DEBUG "VC XLim Lo    = 0x%0X\n",
	       cmd.buffer.block_data[7]);
	printk(KERN_DEBUG "VC YLim Hi    = 0x%0X\n",
	       cmd.buffer.block_data[8]);
	printk(KERN_DEBUG "VC YLim Lo    = 0x%0X\n",
	       cmd.buffer.block_data[9]);
	printk(KERN_DEBUG "VC OHSize     = 0x%0X\n",
	       cmd.buffer.block_data[10]);
	printk(KERN_DEBUG "VC OVSize     = 0x%0X\n",
	       cmd.buffer.block_data[11]);
	printk(KERN_DEBUG "VC HCrop      = 0x%0X\n",
	       cmd.buffer.block_data[12]);
	printk(KERN_DEBUG "VC VCrop      = 0x%0X\n",
	       cmd.buffer.block_data[13]);
	printk(KERN_DEBUG "VC HPhase     = 0x%0X\n",
	       cmd.buffer.block_data[14]);
	printk(KERN_DEBUG "VC VPhase     = 0x%0X\n",
	       cmd.buffer.block_data[15]);
	printk(KERN_DEBUG "VC HIspan     = 0x%0X\n",
	       cmd.buffer.block_data[16]);
	printk(KERN_DEBUG "VC VIspan     = 0x%0X\n",
	       cmd.buffer.block_data[17]);
	printk(KERN_DEBUG "VC HiCrop     = 0x%0X\n",
	       cmd.buffer.block_data[18]);
	printk(KERN_DEBUG "VC ViCrop     = 0x%0X\n",
	       cmd.buffer.block_data[19]);
	printk(KERN_DEBUG "VC HiFract    = 0x%0X\n",
	       cmd.buffer.block_data[20]);
	printk(KERN_DEBUG "VC ViFract    = 0x%0X\n",
	       cmd.buffer.block_data[21]);
	printk(KERN_DEBUG "VC JPeg Opt   = 0x%0X\n",
	       cmd.buffer.block_data[22]);
	printk(KERN_DEBUG "VC Creep Per  = 0x%0X\n",
	       cmd.buffer.block_data[23]);
	printk(KERN_DEBUG "VC User Sq.   = 0x%0X\n",
	       cmd.buffer.block_data[24]);
	printk(KERN_DEBUG "VC Target KB  = 0x%0X\n",
	       cmd.buffer.block_data[25]);

	/*** VP ***/
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
	cmd.reg_count = 14;
	cmd.start = 0;
	cpia2_send_command(cam, &cmd);

	printk(KERN_DEBUG "VP Dev Hi     = 0x%0X\n",
	       cmd.buffer.block_data[0]);
	printk(KERN_DEBUG "VP Dev Lo     = 0x%0X\n",
	       cmd.buffer.block_data[1]);
	printk(KERN_DEBUG "VP Sys State  = 0x%0X\n",
	       cmd.buffer.block_data[2]);
	printk(KERN_DEBUG "VP Sys Ctrl   = 0x%0X\n",
	       cmd.buffer.block_data[3]);
	printk(KERN_DEBUG "VP Sensor flg = 0x%0X\n",
	       cmd.buffer.block_data[5]);
	printk(KERN_DEBUG "VP Sensor Rev = 0x%0X\n",
	       cmd.buffer.block_data[6]);
	printk(KERN_DEBUG "VP Dev Config = 0x%0X\n",
	       cmd.buffer.block_data[7]);
	printk(KERN_DEBUG "VP GPIO_DIR   = 0x%0X\n",
	       cmd.buffer.block_data[8]);
	printk(KERN_DEBUG "VP GPIO_DATA  = 0x%0X\n",
	       cmd.buffer.block_data[9]);
	printk(KERN_DEBUG "VP Ram ADDR H = 0x%0X\n",
	       cmd.buffer.block_data[10]);
	printk(KERN_DEBUG "VP Ram ADDR L = 0x%0X\n",
	       cmd.buffer.block_data[11]);
	printk(KERN_DEBUG "VP RAM Data   = 0x%0X\n",
	       cmd.buffer.block_data[12]);
	printk(KERN_DEBUG "Do Call       = 0x%0X\n",
	       cmd.buffer.block_data[13]);

	if (cam->params.pnp_id.device_type == DEVICE_STV_672) {
		cmd.reg_count = 9;
		cmd.start = 0x0E;
		cpia2_send_command(cam, &cmd);
		printk(KERN_DEBUG "VP Clock Ctrl = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		printk(KERN_DEBUG "VP Patch Rev  = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		printk(KERN_DEBUG "VP Vid Mode   = 0x%0X\n",
		       cmd.buffer.block_data[2]);
		printk(KERN_DEBUG "VP Framerate  = 0x%0X\n",
		       cmd.buffer.block_data[3]);
		printk(KERN_DEBUG "VP UserEffect = 0x%0X\n",
		       cmd.buffer.block_data[4]);
		printk(KERN_DEBUG "VP White Bal  = 0x%0X\n",
		       cmd.buffer.block_data[5]);
		printk(KERN_DEBUG "VP WB thresh  = 0x%0X\n",
		       cmd.buffer.block_data[6]);
		printk(KERN_DEBUG "VP Exp Modes  = 0x%0X\n",
		       cmd.buffer.block_data[7]);
		printk(KERN_DEBUG "VP Exp Target = 0x%0X\n",
		       cmd.buffer.block_data[8]);

		cmd.reg_count = 1;
		cmd.start = 0x1B;
		cpia2_send_command(cam, &cmd);
		printk(KERN_DEBUG "VP FlickerMds = 0x%0X\n",
		       cmd.buffer.block_data[0]);
	} else {
		cmd.reg_count = 8 ;
		cmd.start = 0x0E;
		cpia2_send_command(cam, &cmd);
		printk(KERN_DEBUG "VP Clock Ctrl = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		printk(KERN_DEBUG "VP Patch Rev  = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		printk(KERN_DEBUG "VP Vid Mode   = 0x%0X\n",
		       cmd.buffer.block_data[5]);
		printk(KERN_DEBUG "VP Framerate  = 0x%0X\n",
		       cmd.buffer.block_data[6]);
		printk(KERN_DEBUG "VP UserEffect = 0x%0X\n",
		       cmd.buffer.block_data[7]);

		cmd.reg_count = 1;
		cmd.start = CPIA2_VP5_EXPOSURE_TARGET;
		cpia2_send_command(cam, &cmd);
		printk(KERN_DEBUG "VP5 Exp Target= 0x%0X\n",
		       cmd.buffer.block_data[0]);

		cmd.reg_count = 4;
		cmd.start = 0x3A;
		cpia2_send_command(cam, &cmd);
		printk(KERN_DEBUG "VP5 MY Black  = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		printk(KERN_DEBUG "VP5 MCY Range = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		printk(KERN_DEBUG "VP5 MYCEILING = 0x%0X\n",
		       cmd.buffer.block_data[2]);
		printk(KERN_DEBUG "VP5 MCUV Sat  = 0x%0X\n",
		       cmd.buffer.block_data[3]);
	}
#endif
}