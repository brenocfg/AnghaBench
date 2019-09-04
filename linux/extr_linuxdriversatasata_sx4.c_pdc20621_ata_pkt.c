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
struct ata_taskfile {scalar_t__ protocol; int flags; int ctl; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ATA_DEV1 ; 
 int ATA_DEVICE_OBS ; 
 scalar_t__ ATA_PROT_DMA ; 
 scalar_t__ ATA_PROT_NODATA ; 
 int ATA_REG_DEVICE ; 
 int ATA_TFLAG_WRITE ; 
 unsigned int PDC_20621_DIMM_BASE ; 
 unsigned int PDC_DIMM_APKT_PRD ; 
 unsigned int PDC_DIMM_ATA_PKT ; 
 unsigned int PDC_DIMM_WINDOW_STEP ; 
 int PDC_PKT_CLEAR_BSY ; 
 int PDC_PKT_NODATA ; 
 int PDC_PKT_READ ; 
 int PDC_REG_DEVCTL ; 
 int /*<<< orphan*/  VPRINTK (char*,unsigned int,unsigned int) ; 
 scalar_t__ cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static inline unsigned int pdc20621_ata_pkt(struct ata_taskfile *tf,
					    unsigned int devno, u8 *buf,
					    unsigned int portno)
{
	unsigned int i, dw;
	__le32 *buf32 = (__le32 *) buf;
	u8 dev_reg;

	unsigned int dimm_sg = PDC_20621_DIMM_BASE +
			       (PDC_DIMM_WINDOW_STEP * portno) +
			       PDC_DIMM_APKT_PRD;
	VPRINTK("ENTER, dimm_sg == 0x%x, %d\n", dimm_sg, dimm_sg);

	i = PDC_DIMM_ATA_PKT;

	/*
	 * Set up ATA packet
	 */
	if ((tf->protocol == ATA_PROT_DMA) && (!(tf->flags & ATA_TFLAG_WRITE)))
		buf[i++] = PDC_PKT_READ;
	else if (tf->protocol == ATA_PROT_NODATA)
		buf[i++] = PDC_PKT_NODATA;
	else
		buf[i++] = 0;
	buf[i++] = 0;			/* reserved */
	buf[i++] = portno + 1;		/* seq. id */
	buf[i++] = 0xff;		/* delay seq. id */

	/* dimm dma S/G, and next-pkt */
	dw = i >> 2;
	if (tf->protocol == ATA_PROT_NODATA)
		buf32[dw] = 0;
	else
		buf32[dw] = cpu_to_le32(dimm_sg);
	buf32[dw + 1] = 0;
	i += 8;

	if (devno == 0)
		dev_reg = ATA_DEVICE_OBS;
	else
		dev_reg = ATA_DEVICE_OBS | ATA_DEV1;

	/* select device */
	buf[i++] = (1 << 5) | PDC_PKT_CLEAR_BSY | ATA_REG_DEVICE;
	buf[i++] = dev_reg;

	/* device control register */
	buf[i++] = (1 << 5) | PDC_REG_DEVCTL;
	buf[i++] = tf->ctl;

	return i;
}