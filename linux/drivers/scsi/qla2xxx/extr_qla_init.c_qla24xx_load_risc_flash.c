#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int uint32_t ;
typedef  int uint ;
struct req_que {scalar_t__ ring; int /*<<< orphan*/  dma; } ;
struct qla_hw_data {int fw_transfer_size; struct fwdt* fwdt; struct req_que** req_q_map; } ;
struct fwdt {int* template; int length; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int BIT_9 ; 
 int FA_RISC_CODE_SEGMENTS ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_read_flash_data (TYPE_1__*,int*,int,int) ; 
 scalar_t__ qla24xx_risc_firmware_invalid (int*) ; 
 int qla27xx_fwdt_template_size (int*) ; 
 int /*<<< orphan*/  qla27xx_fwdt_template_valid (int*) ; 
 int qla2x00_load_ram (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int swab32 (int) ; 
 int /*<<< orphan*/  vfree (int*) ; 
 int* vmalloc (int) ; 

__attribute__((used)) static int
qla24xx_load_risc_flash(scsi_qla_host_t *vha, uint32_t *srisc_addr,
    uint32_t faddr)
{
	int rval;
	uint templates, segments, fragment;
	ulong i;
	uint j;
	ulong dlen;
	uint32_t *dcode;
	uint32_t risc_addr, risc_size, risc_attr = 0;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];
	struct fwdt *fwdt = ha->fwdt;

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "FW: Loading firmware from flash (%x).\n", faddr);

	dcode = (void *)req->ring;
	qla24xx_read_flash_data(vha, dcode, faddr, 8);
	if (qla24xx_risc_firmware_invalid(dcode)) {
		ql_log(ql_log_fatal, vha, 0x008c,
		    "Unable to verify the integrity of flash firmware "
		    "image.\n");
		ql_log(ql_log_fatal, vha, 0x008d,
		    "Firmware data: %08x %08x %08x %08x.\n",
		    dcode[0], dcode[1], dcode[2], dcode[3]);

		return QLA_FUNCTION_FAILED;
	}

	dcode = (void *)req->ring;
	*srisc_addr = 0;
	segments = FA_RISC_CODE_SEGMENTS;
	for (j = 0; j < segments; j++) {
		ql_dbg(ql_dbg_init, vha, 0x008d,
		    "-> Loading segment %u...\n", j);
		qla24xx_read_flash_data(vha, dcode, faddr, 10);
		risc_addr = be32_to_cpu(dcode[2]);
		risc_size = be32_to_cpu(dcode[3]);
		if (!*srisc_addr) {
			*srisc_addr = risc_addr;
			risc_attr = be32_to_cpu(dcode[9]);
		}

		dlen = ha->fw_transfer_size >> 2;
		for (fragment = 0; risc_size; fragment++) {
			if (dlen > risc_size)
				dlen = risc_size;

			ql_dbg(ql_dbg_init, vha, 0x008e,
			    "-> Loading fragment %u: %#x <- %#x (%#lx dwords)...\n",
			    fragment, risc_addr, faddr, dlen);
			qla24xx_read_flash_data(vha, dcode, faddr, dlen);
			for (i = 0; i < dlen; i++)
				dcode[i] = swab32(dcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr, dlen);
			if (rval) {
				ql_log(ql_log_fatal, vha, 0x008f,
				    "-> Failed load firmware fragment %u.\n",
				    fragment);
				return QLA_FUNCTION_FAILED;
			}

			faddr += dlen;
			risc_addr += dlen;
			risc_size -= dlen;
		}
	}

	if (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		return QLA_SUCCESS;

	templates = (risc_attr & BIT_9) ? 2 : 1;
	ql_dbg(ql_dbg_init, vha, 0x0160, "-> templates = %u\n", templates);
	for (j = 0; j < templates; j++, fwdt++) {
		if (fwdt->template)
			vfree(fwdt->template);
		fwdt->template = NULL;
		fwdt->length = 0;

		dcode = (void *)req->ring;
		qla24xx_read_flash_data(vha, dcode, faddr, 7);
		risc_size = be32_to_cpu(dcode[2]);
		ql_dbg(ql_dbg_init, vha, 0x0161,
		    "-> fwdt%u template array at %#x (%#x dwords)\n",
		    j, faddr, risc_size);
		if (!risc_size || !~risc_size) {
			ql_dbg(ql_dbg_init, vha, 0x0162,
			    "-> fwdt%u failed to read array\n", j);
			goto failed;
		}

		/* skip header and ignore checksum */
		faddr += 7;
		risc_size -= 8;

		ql_dbg(ql_dbg_init, vha, 0x0163,
		    "-> fwdt%u template allocate template %#x words...\n",
		    j, risc_size);
		fwdt->template = vmalloc(risc_size * sizeof(*dcode));
		if (!fwdt->template) {
			ql_log(ql_log_warn, vha, 0x0164,
			    "-> fwdt%u failed allocate template.\n", j);
			goto failed;
		}

		dcode = fwdt->template;
		qla24xx_read_flash_data(vha, dcode, faddr, risc_size);

		if (!qla27xx_fwdt_template_valid(dcode)) {
			ql_log(ql_log_warn, vha, 0x0165,
			    "-> fwdt%u failed template validate\n", j);
			goto failed;
		}

		dlen = qla27xx_fwdt_template_size(dcode);
		ql_dbg(ql_dbg_init, vha, 0x0166,
		    "-> fwdt%u template size %#lx bytes (%#lx words)\n",
		    j, dlen, dlen / sizeof(*dcode));
		if (dlen > risc_size * sizeof(*dcode)) {
			ql_log(ql_log_warn, vha, 0x0167,
			    "-> fwdt%u template exceeds array (%-lu bytes)\n",
			    j, dlen - risc_size * sizeof(*dcode));
			goto failed;
		}

		fwdt->length = dlen;
		ql_dbg(ql_dbg_init, vha, 0x0168,
		    "-> fwdt%u loaded template ok\n", j);

		faddr += risc_size + 1;
	}

	return QLA_SUCCESS;

failed:
	if (fwdt->template)
		vfree(fwdt->template);
	fwdt->template = NULL;
	fwdt->length = 0;

	return QLA_SUCCESS;
}