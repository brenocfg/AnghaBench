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
struct seq_file {int dummy; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int cim_la_show_t6(struct seq_file *seq, void *v, int idx)
{
	if (v == SEQ_START_TOKEN) {
		seq_puts(seq, "Status   Inst    Data      PC     LS0Stat  "
			 "LS0Addr  LS0Data  LS1Stat  LS1Addr  LS1Data\n");
	} else {
		const u32 *p = v;

		seq_printf(seq, "  %02x   %04x%04x %04x%04x %04x%04x %08x %08x %08x %08x %08x %08x\n",
			   (p[9] >> 16) & 0xff,       /* Status */
			   p[9] & 0xffff, p[8] >> 16, /* Inst */
			   p[8] & 0xffff, p[7] >> 16, /* Data */
			   p[7] & 0xffff, p[6] >> 16, /* PC */
			   p[2], p[1], p[0],      /* LS0 Stat, Addr and Data */
			   p[5], p[4], p[3]);     /* LS1 Stat, Addr and Data */
	}
	return 0;
}