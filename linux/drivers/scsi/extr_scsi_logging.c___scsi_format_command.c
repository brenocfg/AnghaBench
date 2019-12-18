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

/* Variables and functions */
 scalar_t__ scnprintf (char*,size_t,char*,unsigned char const) ; 
 int scsi_command_size (unsigned char const*) ; 
 size_t scsi_format_opcode_name (char*,size_t,unsigned char const*) ; 

size_t __scsi_format_command(char *logbuf, size_t logbuf_len,
			     const unsigned char *cdb, size_t cdb_len)
{
	int len, k;
	size_t off;

	off = scsi_format_opcode_name(logbuf, logbuf_len, cdb);
	if (off >= logbuf_len)
		return off;
	len = scsi_command_size(cdb);
	if (cdb_len < len)
		len = cdb_len;
	/* print out all bytes in cdb */
	for (k = 0; k < len; ++k) {
		if (off > logbuf_len - 3)
			break;
		off += scnprintf(logbuf + off, logbuf_len - off,
				 " %02x", cdb[k]);
	}
	return off;
}