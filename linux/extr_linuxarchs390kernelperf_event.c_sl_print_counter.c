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
struct cpumf_ctr_info {int /*<<< orphan*/  auth_ctl; int /*<<< orphan*/  csvn; int /*<<< orphan*/  cfvn; } ;
typedef  int /*<<< orphan*/  ci ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cpumf_ctr_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qctri (struct cpumf_ctr_info*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sl_print_counter(struct seq_file *m)
{
	struct cpumf_ctr_info ci;

	memset(&ci, 0, sizeof(ci));
	if (qctri(&ci))
		return;

	seq_printf(m, "CPU-MF: Counter facility: version=%u.%u "
		   "authorization=%04x\n", ci.cfvn, ci.csvn, ci.auth_ctl);
}