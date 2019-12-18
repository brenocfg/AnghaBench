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
typedef  int uint32_t ;
struct scsi_qla_host {int host_no; int fw_dump_tmplt_size; int fw_dump_capture_mask; int fw_dump_size; TYPE_1__* pdev; scalar_t__ fw_dump; scalar_t__ fw_dump_tmplt_hdr; int /*<<< orphan*/  flags; } ;
struct qla4_8xxx_minidump_template_hdr {int capture_debug_level; int driver_capture_mask; int num_of_entries; scalar_t__* capture_size_array; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_82XX_FW_DUMPED ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,...) ; 
 int ql4xmdcapmask ; 
 int qla4_80xx_is_minidump_dma_capable (struct scsi_qla_host*,struct qla4_8xxx_minidump_template_hdr*) ; 
 int qla4xxx_get_minidump_template (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla4xxx_req_template_size (struct scsi_qla_host*) ; 
 scalar_t__ vmalloc (int) ; 

void qla4xxx_alloc_fw_dump(struct scsi_qla_host *ha)
{
	int status;
	uint32_t capture_debug_level;
	int hdr_entry_bit, k;
	void *md_tmp;
	dma_addr_t md_tmp_dma;
	struct qla4_8xxx_minidump_template_hdr *md_hdr;
	int dma_capable;

	if (ha->fw_dump) {
		ql4_printk(KERN_WARNING, ha,
			   "Firmware dump previously allocated.\n");
		return;
	}

	status = qla4xxx_req_template_size(ha);
	if (status != QLA_SUCCESS) {
		ql4_printk(KERN_INFO, ha,
			   "scsi%ld: Failed to get template size\n",
			   ha->host_no);
		return;
	}

	clear_bit(AF_82XX_FW_DUMPED, &ha->flags);

	/* Allocate memory for saving the template */
	md_tmp = dma_alloc_coherent(&ha->pdev->dev, ha->fw_dump_tmplt_size,
				    &md_tmp_dma, GFP_KERNEL);
	if (!md_tmp) {
		ql4_printk(KERN_INFO, ha,
			   "scsi%ld: Failed to allocate DMA memory\n",
			   ha->host_no);
		return;
	}

	/* Request template */
	status =  qla4xxx_get_minidump_template(ha, md_tmp_dma);
	if (status != QLA_SUCCESS) {
		ql4_printk(KERN_INFO, ha,
			   "scsi%ld: Failed to get minidump template\n",
			   ha->host_no);
		goto alloc_cleanup;
	}

	md_hdr = (struct qla4_8xxx_minidump_template_hdr *)md_tmp;

	dma_capable = qla4_80xx_is_minidump_dma_capable(ha, md_hdr);

	capture_debug_level = md_hdr->capture_debug_level;

	/* Get capture mask based on module loadtime setting. */
	if ((ql4xmdcapmask >= 0x3 && ql4xmdcapmask <= 0x7F) ||
	    (ql4xmdcapmask == 0xFF && dma_capable))  {
		ha->fw_dump_capture_mask = ql4xmdcapmask;
	} else {
		if (ql4xmdcapmask == 0xFF)
			ql4_printk(KERN_INFO, ha, "Falling back to default capture mask, as PEX DMA is not supported\n");
		ha->fw_dump_capture_mask = capture_debug_level;
	}

	md_hdr->driver_capture_mask = ha->fw_dump_capture_mask;

	DEBUG2(ql4_printk(KERN_INFO, ha, "Minimum num of entries = %d\n",
			  md_hdr->num_of_entries));
	DEBUG2(ql4_printk(KERN_INFO, ha, "Dump template size  = %d\n",
			  ha->fw_dump_tmplt_size));
	DEBUG2(ql4_printk(KERN_INFO, ha, "Selected Capture mask =0x%x\n",
			  ha->fw_dump_capture_mask));

	/* Calculate fw_dump_size */
	for (hdr_entry_bit = 0x2, k = 1; (hdr_entry_bit & 0xFF);
	     hdr_entry_bit <<= 1, k++) {
		if (hdr_entry_bit & ha->fw_dump_capture_mask)
			ha->fw_dump_size += md_hdr->capture_size_array[k];
	}

	/* Total firmware dump size including command header */
	ha->fw_dump_size += ha->fw_dump_tmplt_size;
	ha->fw_dump = vmalloc(ha->fw_dump_size);
	if (!ha->fw_dump)
		goto alloc_cleanup;

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "Minidump Template Size = 0x%x KB\n",
			  ha->fw_dump_tmplt_size));
	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "Total Minidump size = 0x%x KB\n", ha->fw_dump_size));

	memcpy(ha->fw_dump, md_tmp, ha->fw_dump_tmplt_size);
	ha->fw_dump_tmplt_hdr = ha->fw_dump;

alloc_cleanup:
	dma_free_coherent(&ha->pdev->dev, ha->fw_dump_tmplt_size,
			  md_tmp, md_tmp_dma);
}