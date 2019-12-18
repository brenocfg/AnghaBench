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
typedef  int u_int ;
struct seq_file {int dummy; } ;
struct ahd_transinfo {scalar_t__ period; scalar_t__ offset; int width; int ppr_options; } ;

/* Variables and functions */
 scalar_t__ AHD_PERIOD_UNKNOWN ; 
 int MSG_EXT_PPR_DT_REQ ; 
 int MSG_EXT_PPR_IU_REQ ; 
 int MSG_EXT_PPR_QAS_REQ ; 
 int MSG_EXT_PPR_RD_STRM ; 
 int MSG_EXT_PPR_RTI ; 
 int ahd_calc_syncsrate (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void
ahd_format_transinfo(struct seq_file *m, struct ahd_transinfo *tinfo)
{
	u_int speed;
	u_int freq;
	u_int mb;

	if (tinfo->period == AHD_PERIOD_UNKNOWN) {
		seq_puts(m, "Renegotiation Pending\n");
		return;
	}
        speed = 3300;
        freq = 0;
	if (tinfo->offset != 0) {
		freq = ahd_calc_syncsrate(tinfo->period);
		speed = freq;
	}
	speed *= (0x01 << tinfo->width);
        mb = speed / 1000;
        if (mb > 0)
		seq_printf(m, "%d.%03dMB/s transfers", mb, speed % 1000);
        else
		seq_printf(m, "%dKB/s transfers", speed);

	if (freq != 0) {
		int	printed_options;

		printed_options = 0;
		seq_printf(m, " (%d.%03dMHz", freq / 1000, freq % 1000);
		if ((tinfo->ppr_options & MSG_EXT_PPR_RD_STRM) != 0) {
			seq_puts(m, " RDSTRM");
			printed_options++;
		}
		if ((tinfo->ppr_options & MSG_EXT_PPR_DT_REQ) != 0) {
			seq_puts(m, printed_options ? "|DT" : " DT");
			printed_options++;
		}
		if ((tinfo->ppr_options & MSG_EXT_PPR_IU_REQ) != 0) {
			seq_puts(m, printed_options ? "|IU" : " IU");
			printed_options++;
		}
		if ((tinfo->ppr_options & MSG_EXT_PPR_RTI) != 0) {
			seq_puts(m, printed_options ? "|RTI" : " RTI");
			printed_options++;
		}
		if ((tinfo->ppr_options & MSG_EXT_PPR_QAS_REQ) != 0) {
			seq_puts(m, printed_options ? "|QAS" : " QAS");
			printed_options++;
		}
	}

	if (tinfo->width > 0) {
		if (freq != 0) {
			seq_puts(m, ", ");
		} else {
			seq_puts(m, " (");
		}
		seq_printf(m, "%dbit)", 8 * (0x01 << tinfo->width));
	} else if (freq != 0) {
		seq_putc(m, ')');
	}
	seq_putc(m, '\n');
}