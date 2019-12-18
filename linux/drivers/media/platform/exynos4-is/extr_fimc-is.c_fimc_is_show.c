#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {struct fimc_is* private; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vaddr; } ;
struct fimc_is {TYPE_2__* pdev; TYPE_1__ memory; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int FIMC_IS_DEBUG_REGION_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int fimc_is_show(struct seq_file *s, void *data)
{
	struct fimc_is *is = s->private;
	const u8 *buf = is->memory.vaddr + FIMC_IS_DEBUG_REGION_OFFSET;

	if (is->memory.vaddr == NULL) {
		dev_err(&is->pdev->dev, "firmware memory is not initialized\n");
		return -EIO;
	}

	seq_printf(s, "%s\n", buf);
	return 0;
}