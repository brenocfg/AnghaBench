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
struct mtd_file_info {int /*<<< orphan*/  mtd; } ;
struct file {struct mtd_file_info* private_data; } ;

/* Variables and functions */
 int mtd_mmap_capabilities (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned mtdchar_mmap_capabilities(struct file *file)
{
	struct mtd_file_info *mfi = file->private_data;

	return mtd_mmap_capabilities(mfi->mtd);
}