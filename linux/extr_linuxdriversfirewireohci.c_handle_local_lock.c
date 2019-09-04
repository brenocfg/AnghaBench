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
struct fw_packet {int /*<<< orphan*/ * header; int /*<<< orphan*/ * payload; } ;
struct fw_ohci {int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  lock_old ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CSR_BUS_MANAGER_ID ; 
 int EXTCODE_COMPARE_SWAP ; 
 int HEADER_GET_DATA_LENGTH (int /*<<< orphan*/ ) ; 
 int HEADER_GET_EXTENDED_TCODE (int /*<<< orphan*/ ) ; 
 int HEADER_GET_TCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OHCI1394_CSRCompareData ; 
 int /*<<< orphan*/  OHCI1394_CSRControl ; 
 int /*<<< orphan*/  OHCI1394_CSRData ; 
 int /*<<< orphan*/  RCODE_BUSY ; 
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 int /*<<< orphan*/  RCODE_TYPE_ERROR ; 
 int TCODE_LOCK_REQUEST ; 
 int TCODE_READ_QUADLET_REQUEST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_core_handle_response (int /*<<< orphan*/ *,struct fw_packet*) ; 
 int /*<<< orphan*/  fw_fill_response (struct fw_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_local_lock(struct fw_ohci *ohci,
			      struct fw_packet *packet, u32 csr)
{
	struct fw_packet response;
	int tcode, length, ext_tcode, sel, try;
	__be32 *payload, lock_old;
	u32 lock_arg, lock_data;

	tcode = HEADER_GET_TCODE(packet->header[0]);
	length = HEADER_GET_DATA_LENGTH(packet->header[3]);
	payload = packet->payload;
	ext_tcode = HEADER_GET_EXTENDED_TCODE(packet->header[3]);

	if (tcode == TCODE_LOCK_REQUEST &&
	    ext_tcode == EXTCODE_COMPARE_SWAP && length == 8) {
		lock_arg = be32_to_cpu(payload[0]);
		lock_data = be32_to_cpu(payload[1]);
	} else if (tcode == TCODE_READ_QUADLET_REQUEST) {
		lock_arg = 0;
		lock_data = 0;
	} else {
		fw_fill_response(&response, packet->header,
				 RCODE_TYPE_ERROR, NULL, 0);
		goto out;
	}

	sel = (csr - CSR_BUS_MANAGER_ID) / 4;
	reg_write(ohci, OHCI1394_CSRData, lock_data);
	reg_write(ohci, OHCI1394_CSRCompareData, lock_arg);
	reg_write(ohci, OHCI1394_CSRControl, sel);

	for (try = 0; try < 20; try++)
		if (reg_read(ohci, OHCI1394_CSRControl) & 0x80000000) {
			lock_old = cpu_to_be32(reg_read(ohci,
							OHCI1394_CSRData));
			fw_fill_response(&response, packet->header,
					 RCODE_COMPLETE,
					 &lock_old, sizeof(lock_old));
			goto out;
		}

	ohci_err(ohci, "swap not done (CSR lock timeout)\n");
	fw_fill_response(&response, packet->header, RCODE_BUSY, NULL, 0);

 out:
	fw_core_handle_response(&ohci->card, &response);
}