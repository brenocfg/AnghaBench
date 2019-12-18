#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* mmc_test_cases ; 
 int /*<<< orphan*/  mmc_test_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int mtf_testlist_show(struct seq_file *sf, void *data)
{
	int i;

	mutex_lock(&mmc_test_lock);

	seq_puts(sf, "0:\tRun all tests\n");
	for (i = 0; i < ARRAY_SIZE(mmc_test_cases); i++)
		seq_printf(sf, "%d:\t%s\n", i + 1, mmc_test_cases[i].name);

	mutex_unlock(&mmc_test_lock);

	return 0;
}