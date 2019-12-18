#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
struct secure_flash_update_block {int dummy; } ;
struct TYPE_21__ {scalar_t__ fac_supported; int /*<<< orphan*/  secure_fw; scalar_t__ secure_adapter; } ;
struct qla_hw_data {int fdt_block_size; TYPE_1__* pdev; TYPE_2__ flags; } ;
struct qla_flt_region {scalar_t__ code; scalar_t__ attribute; } ;
struct TYPE_22__ {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_20__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_9 ; 
 int /*<<< orphan*/  FAC_SEMAPHORE_LOCK ; 
 int /*<<< orphan*/  FAC_SEMAPHORE_UNLOCK ; 
 int /*<<< orphan*/  FLASH_SEMAPHORE_REGISTER_ADDR ; 
 scalar_t__ FLT_REG_FW ; 
 scalar_t__ FLT_REG_FW_SEC_27XX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  ISP_ABORT_TO_ROM ; 
 int OPTROM_BURST_DWORDS ; 
 int OPTROM_BURST_SIZE ; 
 int QLA_COMMAND_ERROR ; 
 int QLA_SUCCESS ; 
 int be32_to_cpu (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  flash_data_addr (struct qla_hw_data*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_3__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 scalar_t__ ql_dbg_verbose ; 
 int /*<<< orphan*/  ql_log (scalar_t__,TYPE_3__*,int,char*,...) ; 
 scalar_t__ ql_log_warn ; 
 int qla24xx_erase_sector (TYPE_3__*,int) ; 
 int qla24xx_protect_flash (TYPE_3__*) ; 
 int qla24xx_unprotect_flash (TYPE_3__*) ; 
 int qla28xx_extract_sfub_and_verify (TYPE_3__*,int*,int,int,int /*<<< orphan*/ *) ; 
 int qla28xx_get_flash_region (TYPE_3__*,int,struct qla_flt_region*) ; 
 int qla28xx_secure_flash_update (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int) ; 
 int qla2x00_load_ram (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int qla2x00_wait_for_chip_reset (TYPE_3__*) ; 
 int qla2x00_wait_for_hba_online (TYPE_3__*) ; 
 int qla2x00_write_ram_word (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_3__*) ; 
 int qla2xxx_write_remote_register (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int qla81xx_fac_semaphore_access (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla28xx_write_flash_data(scsi_qla_host_t *vha, uint32_t *dwptr, uint32_t faddr,
    uint32_t dwords)
{
	struct qla_hw_data *ha = vha->hw;
	ulong liter;
	ulong dburst = OPTROM_BURST_DWORDS; /* burst size in dwords */
	uint32_t sec_mask, rest_addr, fdata;
	void *optrom = NULL;
	dma_addr_t optrom_dma;
	int rval;
	struct secure_flash_update_block *sfub;
	dma_addr_t sfub_dma;
	uint32_t offset = faddr << 2;
	uint32_t buf_size_without_sfub = 0;
	struct qla_flt_region region;
	bool reset_to_rom = false;
	uint32_t risc_size, risc_attr = 0;
	uint32_t *fw_array = NULL;

	/* Retrieve region info - must be a start address passed in */
	rval = qla28xx_get_flash_region(vha, offset, &region);

	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0xffff,
		    "Invalid address %x - not a region start address\n",
		    offset);
		goto done;
	}

	/* Allocate dma buffer for burst write */
	optrom = dma_alloc_coherent(&ha->pdev->dev, OPTROM_BURST_SIZE,
	    &optrom_dma, GFP_KERNEL);
	if (!optrom) {
		ql_log(ql_log_warn, vha, 0x7095,
		    "Failed allocate burst (%x bytes)\n", OPTROM_BURST_SIZE);
		rval = QLA_COMMAND_ERROR;
		goto done;
	}

	/*
	 * If adapter supports secure flash and region is secure
	 * extract secure flash update block (SFUB) and verify
	 */
	if (ha->flags.secure_adapter && region.attribute) {

		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
		    "Region %x is secure\n", region.code);

		if (region.code == FLT_REG_FW ||
		    region.code == FLT_REG_FW_SEC_27XX) {
			fw_array = dwptr;

			/* 1st fw array */
			risc_size = be32_to_cpu(fw_array[3]);
			risc_attr = be32_to_cpu(fw_array[9]);

			buf_size_without_sfub = risc_size;
			fw_array += risc_size;

			/* 2nd fw array */
			risc_size = be32_to_cpu(fw_array[3]);

			buf_size_without_sfub += risc_size;
			fw_array += risc_size;

			/* 1st dump template */
			risc_size = be32_to_cpu(fw_array[2]);

			/* skip header and ignore checksum */
			buf_size_without_sfub += risc_size;
			fw_array += risc_size;

			if (risc_attr & BIT_9) {
				/* 2nd dump template */
				risc_size = be32_to_cpu(fw_array[2]);

				/* skip header and ignore checksum */
				buf_size_without_sfub += risc_size;
				fw_array += risc_size;
			}
		} else {
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Secure region %x not supported\n",
			    region.code);
			rval = QLA_COMMAND_ERROR;
			goto done;
		}

		sfub = dma_alloc_coherent(&ha->pdev->dev,
			sizeof(struct secure_flash_update_block), &sfub_dma,
			GFP_KERNEL);
		if (!sfub) {
			ql_log(ql_log_warn, vha, 0xffff,
			    "Unable to allocate memory for SFUB\n");
			rval = QLA_COMMAND_ERROR;
			goto done;
		}

		rval = qla28xx_extract_sfub_and_verify(vha, dwptr, dwords,
			buf_size_without_sfub, (uint8_t *)sfub);

		if (rval != QLA_SUCCESS)
			goto done;

		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
		    "SFUB extract and verify successful\n");
	}

	rest_addr = (ha->fdt_block_size >> 2) - 1;
	sec_mask = ~rest_addr;

	/* Lock semaphore */
	rval = qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_LOCK);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0xffff,
		    "Unable to lock flash semaphore.");
		goto done;
	}

	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Unprotect flash...\n");
	rval = qla24xx_unprotect_flash(vha);
	if (rval) {
		qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_UNLOCK);
		ql_log(ql_log_warn, vha, 0x7096, "Failed unprotect flash\n");
		goto done;
	}

	for (liter = 0; liter < dwords; liter++, faddr++) {
		fdata = (faddr & sec_mask) << 2;

		/* If start of sector */
		if (!(faddr & rest_addr)) {
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
			    "Erase sector %#x...\n", faddr);
			rval = qla24xx_erase_sector(vha, fdata);
			if (rval) {
				ql_dbg(ql_dbg_user, vha, 0x7007,
				    "Failed erase sector %#x\n", faddr);
				goto write_protect;
			}
		}
	}

	if (ha->flags.secure_adapter) {
		/*
		 * If adapter supports secure flash but FW doesn't,
		 * disable write protect, release semaphore and reset
		 * chip to execute ROM code in order to update region securely
		 */
		if (!ha->flags.secure_fw) {
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Disable Write and Release Semaphore.");
			rval = qla24xx_protect_flash(vha);
			if (rval != QLA_SUCCESS) {
				qla81xx_fac_semaphore_access(vha,
					FAC_SEMAPHORE_UNLOCK);
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to protect flash.");
				goto done;
			}

			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Reset chip to ROM.");
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			set_bit(ISP_ABORT_TO_ROM, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			rval = qla2x00_wait_for_chip_reset(vha);
			if (rval != QLA_SUCCESS) {
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to reset to ROM code.");
				goto done;
			}
			reset_to_rom = true;
			ha->flags.fac_supported = 0;

			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Lock Semaphore");
			rval = qla2xxx_write_remote_register(vha,
			    FLASH_SEMAPHORE_REGISTER_ADDR, 0x00020002);
			if (rval != QLA_SUCCESS) {
				ql_log(ql_log_warn, vha, 0xffff,
				    "Unable to lock flash semaphore.");
				goto done;
			}

			/* Unprotect flash */
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Enable Write.");
			rval = qla2x00_write_ram_word(vha, 0x7ffd0101, 0);
			if (rval) {
				ql_log(ql_log_warn, vha, 0x7096,
				    "Failed unprotect flash\n");
				goto done;
			}
		}

		/* If region is secure, send Secure Flash MB Cmd */
		if (region.attribute && buf_size_without_sfub) {
			ql_log(ql_log_warn + ql_dbg_verbose, vha, 0xffff,
			    "Sending Secure Flash MB Cmd\n");
			rval = qla28xx_secure_flash_update(vha, 0, region.code,
				buf_size_without_sfub, sfub_dma,
				sizeof(struct secure_flash_update_block));
			if (rval != QLA_SUCCESS) {
				ql_log(ql_log_warn, vha, 0xffff,
				    "Secure Flash MB Cmd failed %x.", rval);
				goto write_protect;
			}
		}

	}

	/* re-init flash offset */
	faddr = offset >> 2;

	for (liter = 0; liter < dwords; liter++, faddr++, dwptr++) {
		fdata = (faddr & sec_mask) << 2;

		/* If smaller than a burst remaining */
		if (dwords - liter < dburst)
			dburst = dwords - liter;

		/* Copy to dma buffer */
		memcpy(optrom, dwptr, dburst << 2);

		/* Burst write */
		ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
		    "Write burst (%#lx dwords)...\n", dburst);
		rval = qla2x00_load_ram(vha, optrom_dma,
		    flash_data_addr(ha, faddr), dburst);
		if (rval != QLA_SUCCESS) {
			ql_log(ql_log_warn, vha, 0x7097,
			    "Failed burst write at %x (%p/%#llx)...\n",
			    flash_data_addr(ha, faddr), optrom,
			    (u64)optrom_dma);
			break;
		}

		liter += dburst - 1;
		faddr += dburst - 1;
		dwptr += dburst - 1;
		continue;
	}

write_protect:
	ql_log(ql_log_warn + ql_dbg_verbose, vha, 0x7095,
	    "Protect flash...\n");
	rval = qla24xx_protect_flash(vha);
	if (rval) {
		qla81xx_fac_semaphore_access(vha, FAC_SEMAPHORE_UNLOCK);
		ql_log(ql_log_warn, vha, 0x7099,
		    "Failed protect flash\n");
	}

	if (reset_to_rom == true) {
		/* Schedule DPC to restart the RISC */
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);

		rval = qla2x00_wait_for_hba_online(vha);
		if (rval != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0xffff,
			    "Adapter did not come out of reset\n");
	}

done:
	if (optrom)
		dma_free_coherent(&ha->pdev->dev,
		    OPTROM_BURST_SIZE, optrom, optrom_dma);

	return rval;
}