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
 int SNIC_TRC_PBLEN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 scalar_t__ snic_get_trc_data (char*,int) ; 

__attribute__((used)) static int
snic_trc_seq_show(struct seq_file *sfp, void *data)
{
	char buf[SNIC_TRC_PBLEN];

	if (snic_get_trc_data(buf, SNIC_TRC_PBLEN) > 0)
		seq_printf(sfp, "%s\n", buf);

	return 0;
}