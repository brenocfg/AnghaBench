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
struct scsi_cmnd {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARBIT_CLEAR ; 
 unsigned char ARBIT_FAIL ; 
 int /*<<< orphan*/  ARBIT_STATUS ; 
 int ARBIT_TIMEOUT_TIME ; 
 unsigned char ARBIT_WIN ; 
 int DID_BUS_BUSY ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int /*<<< orphan*/  EXT_PORT ; 
 int FALSE ; 
 int /*<<< orphan*/  LED_ON ; 
 int /*<<< orphan*/  NSP32_DEBUG_AUTOSCSI ; 
 int /*<<< orphan*/  SET_ARBIT ; 
 int TRUE ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_index_write1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsp32_arbitration(struct scsi_cmnd *SCpnt, unsigned int base)
{
	unsigned char arbit;
	int	      status = TRUE;
	int	      time   = 0;

	do {
		arbit = nsp32_read1(base, ARBIT_STATUS);
		time++;
	} while ((arbit & (ARBIT_WIN | ARBIT_FAIL)) == 0 &&
		 (time <= ARBIT_TIMEOUT_TIME));

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI,
		  "arbit: 0x%x, delay time: %d", arbit, time);

	if (arbit & ARBIT_WIN) {
		/* Arbitration succeeded */
		SCpnt->result = DID_OK << 16;
		nsp32_index_write1(base, EXT_PORT, LED_ON); /* PCI LED on */
	} else if (arbit & ARBIT_FAIL) {
		/* Arbitration failed */
		SCpnt->result = DID_BUS_BUSY << 16;
		status = FALSE;
	} else {
		/*
		 * unknown error or ARBIT_GO timeout,
		 * something lock up! guess no connection.
		 */
		nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "arbit timeout");
		SCpnt->result = DID_NO_CONNECT << 16;
		status = FALSE;
        }

	/*
	 * clear Arbit
	 */
	nsp32_write1(base, SET_ARBIT, ARBIT_CLEAR);

	return status;
}