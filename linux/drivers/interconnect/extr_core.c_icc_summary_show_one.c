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
struct icc_node {int /*<<< orphan*/  peak_bw; int /*<<< orphan*/  avg_bw; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icc_summary_show_one(struct seq_file *s, struct icc_node *n)
{
	if (!n)
		return;

	seq_printf(s, "%-30s %12u %12u\n",
		   n->name, n->avg_bw, n->peak_bw);
}