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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int ulprx_la_show(struct seq_file *seq, void *v, int idx)
{
	const u32 *p = v;

	if (v == SEQ_START_TOKEN)
		seq_puts(seq, "      Pcmd        Type   Message"
			 "                Data\n");
	else
		seq_printf(seq, "%08x%08x  %4x  %08x  %08x%08x%08x%08x\n",
			   p[1], p[0], p[2], p[3], p[7], p[6], p[5], p[4]);
	return 0;
}