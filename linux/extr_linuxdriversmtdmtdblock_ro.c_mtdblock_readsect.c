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
struct mtd_blktrans_dev {int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 scalar_t__ mtd_read (int /*<<< orphan*/ ,unsigned long,int,size_t*,char*) ; 

__attribute__((used)) static int mtdblock_readsect(struct mtd_blktrans_dev *dev,
			      unsigned long block, char *buf)
{
	size_t retlen;

	if (mtd_read(dev->mtd, (block * 512), 512, &retlen, buf))
		return 1;
	return 0;
}