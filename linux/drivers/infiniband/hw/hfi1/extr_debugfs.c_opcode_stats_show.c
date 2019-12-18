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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int SEQ_SKIP ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int opcode_stats_show(struct seq_file *s, u8 i, u64 packets, u64 bytes)
{
	if (!packets && !bytes)
		return SEQ_SKIP;
	seq_printf(s, "%02x %llu/%llu\n", i,
		   (unsigned long long)packets,
		   (unsigned long long)bytes);

	return 0;
}