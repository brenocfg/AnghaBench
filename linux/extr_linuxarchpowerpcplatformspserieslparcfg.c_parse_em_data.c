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
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  H_GET_EM_PARMS ; 
 scalar_t__ H_SUCCESS ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ plpar_hcall (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 

__attribute__((used)) static void parse_em_data(struct seq_file *m)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	if (firmware_has_feature(FW_FEATURE_LPAR) &&
	    plpar_hcall(H_GET_EM_PARMS, retbuf) == H_SUCCESS)
		seq_printf(m, "power_mode_data=%016lx\n", retbuf[0]);
}