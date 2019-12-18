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
struct trace_seq {int dummy; } ;
typedef  unsigned char sector_t ;

/* Variables and functions */
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
scsi_trace_rw6(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = trace_seq_buffer_ptr(p);
	sector_t lba = 0, txlen = 0;

	lba |= ((cdb[1] & 0x1F) << 16);
	lba |=  (cdb[2] << 8);
	lba |=   cdb[3];
	txlen = cdb[4];

	trace_seq_printf(p, "lba=%llu txlen=%llu",
			 (unsigned long long)lba, (unsigned long long)txlen);
	trace_seq_putc(p, 0);

	return ret;
}