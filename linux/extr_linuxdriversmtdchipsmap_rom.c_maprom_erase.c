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
struct mtd_info {int dummy; } ;
struct erase_info {int dummy; } ;

/* Variables and functions */
 int EROFS ; 

__attribute__((used)) static int maprom_erase (struct mtd_info *mtd, struct erase_info *info)
{
	/* We do our best 8) */
	return -EROFS;
}