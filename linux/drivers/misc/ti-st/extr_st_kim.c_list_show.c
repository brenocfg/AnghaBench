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
struct seq_file {scalar_t__ private; } ;
struct kim_data_s {int /*<<< orphan*/  core_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kim_st_list_protocols (int /*<<< orphan*/ ,struct seq_file*) ; 

__attribute__((used)) static int list_show(struct seq_file *s, void *unused)
{
	struct kim_data_s *kim_gdata = (struct kim_data_s *)s->private;
	kim_st_list_protocols(kim_gdata->core_data, s);
	return 0;
}