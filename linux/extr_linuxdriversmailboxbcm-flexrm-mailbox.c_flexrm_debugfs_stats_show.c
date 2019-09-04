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
struct seq_file {int /*<<< orphan*/  private; } ;
struct platform_device {int dummy; } ;
struct flexrm_mbox {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flexrm_write_stats_in_seqfile (struct flexrm_mbox*,struct seq_file*) ; 
 struct flexrm_mbox* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexrm_debugfs_stats_show(struct seq_file *file, void *offset)
{
	struct platform_device *pdev = to_platform_device(file->private);
	struct flexrm_mbox *mbox = platform_get_drvdata(pdev);

	/* Write stats in file */
	flexrm_write_stats_in_seqfile(mbox, file);

	return 0;
}