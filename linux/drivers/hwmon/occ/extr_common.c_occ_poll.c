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
typedef  int u16 ;
struct occ_poll_response_header {scalar_t__ occ_state; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct occ {int poll_cmd_data; int seq_no; int (* send_cmd ) (struct occ*,int*) ;int last_error; int error; scalar_t__ last_safe; TYPE_1__ resp; scalar_t__ error_count; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 scalar_t__ OCC_ERROR_COUNT_THRESHOLD ; 
 scalar_t__ OCC_SAFE_TIMEOUT ; 
 scalar_t__ OCC_STATE_SAFE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  occ_sysfs_poll_done (struct occ*) ; 
 int stub1 (struct occ*,int*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int occ_poll(struct occ *occ)
{
	int rc;
	u16 checksum = occ->poll_cmd_data + occ->seq_no + 1;
	u8 cmd[8];
	struct occ_poll_response_header *header;

	/* big endian */
	cmd[0] = occ->seq_no++;		/* sequence number */
	cmd[1] = 0;			/* cmd type */
	cmd[2] = 0;			/* data length msb */
	cmd[3] = 1;			/* data length lsb */
	cmd[4] = occ->poll_cmd_data;	/* data */
	cmd[5] = checksum >> 8;		/* checksum msb */
	cmd[6] = checksum & 0xFF;	/* checksum lsb */
	cmd[7] = 0;

	/* mutex should already be locked if necessary */
	rc = occ->send_cmd(occ, cmd);
	if (rc) {
		occ->last_error = rc;
		if (occ->error_count++ > OCC_ERROR_COUNT_THRESHOLD)
			occ->error = rc;

		goto done;
	}

	/* clear error since communication was successful */
	occ->error_count = 0;
	occ->last_error = 0;
	occ->error = 0;

	/* check for safe state */
	header = (struct occ_poll_response_header *)occ->resp.data;
	if (header->occ_state == OCC_STATE_SAFE) {
		if (occ->last_safe) {
			if (time_after(jiffies,
				       occ->last_safe + OCC_SAFE_TIMEOUT))
				occ->error = -EHOSTDOWN;
		} else {
			occ->last_safe = jiffies;
		}
	} else {
		occ->last_safe = 0;
	}

done:
	occ_sysfs_poll_done(occ);
	return rc;
}