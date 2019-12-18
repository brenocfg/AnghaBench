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
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  seq_hex_dump (struct seq_file*,char const*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 

__attribute__((used)) static void wil_seq_hexdump(struct seq_file *s, void *p, int len,
			    const char *prefix)
{
	seq_hex_dump(s, prefix, DUMP_PREFIX_NONE, 16, 1, p, len, false);
}