#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct TYPE_2__ {int /*<<< orphan*/  min_ver; int /*<<< orphan*/  maj_ver; int /*<<< orphan*/  chip; int /*<<< orphan*/  full; } ;
struct kim_data_s {TYPE_1__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int version_show(struct seq_file *s, void *unused)
{
	struct kim_data_s *kim_gdata = (struct kim_data_s *)s->private;
	seq_printf(s, "%04X %d.%d.%d\n", kim_gdata->version.full,
			kim_gdata->version.chip, kim_gdata->version.maj_ver,
			kim_gdata->version.min_ver);
	return 0;
}