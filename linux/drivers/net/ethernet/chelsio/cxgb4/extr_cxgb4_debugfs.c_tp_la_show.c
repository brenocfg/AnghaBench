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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  field_desc_show (struct seq_file*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_la0 ; 

__attribute__((used)) static int tp_la_show(struct seq_file *seq, void *v, int idx)
{
	const u64 *p = v;

	field_desc_show(seq, *p, tp_la0);
	return 0;
}