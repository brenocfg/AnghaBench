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
typedef  int u8 ;
typedef  int u32 ;
struct sata_fsl_port_priv {int cmdentry_paddr; TYPE_1__* cmdslot; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {void* desc_info; void* ttl; void* prde_fis_len; void* cda; } ;

/* Variables and functions */
 unsigned int SATA_FSL_CMD_DESC_SIZE ; 
 int /*<<< orphan*/  VPRINTK (char*,void*,void*,void*,void*) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void sata_fsl_setup_cmd_hdr_entry(struct sata_fsl_port_priv *pp,
					 unsigned int tag, u32 desc_info,
					 u32 data_xfer_len, u8 num_prde,
					 u8 fis_len)
{
	dma_addr_t cmd_descriptor_address;

	cmd_descriptor_address = pp->cmdentry_paddr +
	    tag * SATA_FSL_CMD_DESC_SIZE;

	/* NOTE: both data_xfer_len & fis_len are Dword counts */

	pp->cmdslot[tag].cda = cpu_to_le32(cmd_descriptor_address);
	pp->cmdslot[tag].prde_fis_len =
	    cpu_to_le32((num_prde << 16) | (fis_len << 2));
	pp->cmdslot[tag].ttl = cpu_to_le32(data_xfer_len & ~0x03);
	pp->cmdslot[tag].desc_info = cpu_to_le32(desc_info | (tag & 0x1F));

	VPRINTK("cda=0x%x, prde_fis_len=0x%x, ttl=0x%x, di=0x%x\n",
		pp->cmdslot[tag].cda,
		pp->cmdslot[tag].prde_fis_len,
		pp->cmdslot[tag].ttl, pp->cmdslot[tag].desc_info);

}