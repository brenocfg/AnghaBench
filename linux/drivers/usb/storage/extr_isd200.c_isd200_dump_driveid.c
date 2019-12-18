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
typedef  int u16 ;
struct us_data {int dummy; } ;

/* Variables and functions */
 size_t ATA_ID_BUF_SIZE ; 
 size_t ATA_ID_CAPABILITY ; 
 size_t ATA_ID_COMMAND_SET_1 ; 
 size_t ATA_ID_COMMAND_SET_2 ; 
 size_t ATA_ID_CONFIG ; 
 size_t ATA_ID_CUR_CYLS ; 
 size_t ATA_ID_CUR_HEADS ; 
 size_t ATA_ID_CUR_SECTORS ; 
 size_t ATA_ID_CYLS ; 
 size_t ATA_ID_DWORD_IO ; 
 size_t ATA_ID_FIELD_VALID ; 
 size_t ATA_ID_FW_REV ; 
 size_t ATA_ID_HEADS ; 
 int ATA_ID_LBA_CAPACITY ; 
 size_t ATA_ID_MAX_MULTSECT ; 
 size_t ATA_ID_MULTSECT ; 
 size_t ATA_ID_OLD_DMA_MODES ; 
 size_t ATA_ID_OLD_PIO_MODES ; 
 size_t ATA_ID_PROD ; 
 size_t ATA_ID_SECTORS ; 
 size_t ATA_ID_SERNO ; 
 int ata_id_u32 (int*,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static void isd200_dump_driveid(struct us_data *us, u16 *id)
{
	usb_stor_dbg(us, "   Identify Data Structure:\n");
	usb_stor_dbg(us, "      config = 0x%x\n",	id[ATA_ID_CONFIG]);
	usb_stor_dbg(us, "      cyls = 0x%x\n",		id[ATA_ID_CYLS]);
	usb_stor_dbg(us, "      heads = 0x%x\n",	id[ATA_ID_HEADS]);
	usb_stor_dbg(us, "      track_bytes = 0x%x\n",	id[4]);
	usb_stor_dbg(us, "      sector_bytes = 0x%x\n", id[5]);
	usb_stor_dbg(us, "      sectors = 0x%x\n",	id[ATA_ID_SECTORS]);
	usb_stor_dbg(us, "      serial_no[0] = 0x%x\n", *(char *)&id[ATA_ID_SERNO]);
	usb_stor_dbg(us, "      buf_type = 0x%x\n",	id[20]);
	usb_stor_dbg(us, "      buf_size = 0x%x\n",	id[ATA_ID_BUF_SIZE]);
	usb_stor_dbg(us, "      ecc_bytes = 0x%x\n",	id[22]);
	usb_stor_dbg(us, "      fw_rev[0] = 0x%x\n",	*(char *)&id[ATA_ID_FW_REV]);
	usb_stor_dbg(us, "      model[0] = 0x%x\n",	*(char *)&id[ATA_ID_PROD]);
	usb_stor_dbg(us, "      max_multsect = 0x%x\n", id[ATA_ID_MAX_MULTSECT] & 0xff);
	usb_stor_dbg(us, "      dword_io = 0x%x\n",	id[ATA_ID_DWORD_IO]);
	usb_stor_dbg(us, "      capability = 0x%x\n",	id[ATA_ID_CAPABILITY] >> 8);
	usb_stor_dbg(us, "      tPIO = 0x%x\n",	  id[ATA_ID_OLD_PIO_MODES] >> 8);
	usb_stor_dbg(us, "      tDMA = 0x%x\n",	  id[ATA_ID_OLD_DMA_MODES] >> 8);
	usb_stor_dbg(us, "      field_valid = 0x%x\n",	id[ATA_ID_FIELD_VALID]);
	usb_stor_dbg(us, "      cur_cyls = 0x%x\n",	id[ATA_ID_CUR_CYLS]);
	usb_stor_dbg(us, "      cur_heads = 0x%x\n",	id[ATA_ID_CUR_HEADS]);
	usb_stor_dbg(us, "      cur_sectors = 0x%x\n",	id[ATA_ID_CUR_SECTORS]);
	usb_stor_dbg(us, "      cur_capacity = 0x%x\n", ata_id_u32(id, 57));
	usb_stor_dbg(us, "      multsect = 0x%x\n",	id[ATA_ID_MULTSECT] & 0xff);
	usb_stor_dbg(us, "      lba_capacity = 0x%x\n", ata_id_u32(id, ATA_ID_LBA_CAPACITY));
	usb_stor_dbg(us, "      command_set_1 = 0x%x\n", id[ATA_ID_COMMAND_SET_1]);
	usb_stor_dbg(us, "      command_set_2 = 0x%x\n", id[ATA_ID_COMMAND_SET_2]);
}