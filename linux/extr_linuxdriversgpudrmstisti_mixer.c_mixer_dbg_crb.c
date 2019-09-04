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
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  GAM_DEPTH_GDP0_ID 133 
#define  GAM_DEPTH_GDP1_ID 132 
#define  GAM_DEPTH_GDP2_ID 131 
#define  GAM_DEPTH_GDP3_ID 130 
 int GAM_DEPTH_MASK_ID ; 
#define  GAM_DEPTH_VID0_ID 129 
#define  GAM_DEPTH_VID1_ID 128 
 int GAM_MIXER_NB_DEPTH_LEVEL ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void mixer_dbg_crb(struct seq_file *s, int val)
{
	int i;

	seq_puts(s, "\tDepth: ");
	for (i = 0; i < GAM_MIXER_NB_DEPTH_LEVEL; i++) {
		switch (val & GAM_DEPTH_MASK_ID) {
		case GAM_DEPTH_VID0_ID:
			seq_puts(s, "VID0");
			break;
		case GAM_DEPTH_VID1_ID:
			seq_puts(s, "VID1");
			break;
		case GAM_DEPTH_GDP0_ID:
			seq_puts(s, "GDP0");
			break;
		case GAM_DEPTH_GDP1_ID:
			seq_puts(s, "GDP1");
			break;
		case GAM_DEPTH_GDP2_ID:
			seq_puts(s, "GDP2");
			break;
		case GAM_DEPTH_GDP3_ID:
			seq_puts(s, "GDP3");
			break;
		default:
			seq_puts(s, "---");
		}

		if (i < GAM_MIXER_NB_DEPTH_LEVEL - 1)
			seq_puts(s, " < ");
		val = val >> 3;
	}
}