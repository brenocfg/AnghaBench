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
 int /*<<< orphan*/  seq_write (struct seq_file*,char const*,size_t) ; 

__attribute__((used)) static inline void write_to_seqfile(void *ctx, const char *str, size_t len,
				    bool cont)
{
	seq_write((struct seq_file *)ctx, str, len);
}