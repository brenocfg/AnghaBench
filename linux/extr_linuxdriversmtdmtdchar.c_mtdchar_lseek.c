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
struct mtd_file_info {TYPE_1__* mtd; } ;
struct file {struct mtd_file_info* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_size_llseek (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t mtdchar_lseek(struct file *file, loff_t offset, int orig)
{
	struct mtd_file_info *mfi = file->private_data;
	return fixed_size_llseek(file, offset, orig, mfi->mtd->size);
}