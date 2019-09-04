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

/* Variables and functions */
 int /*<<< orphan*/  BCM963XX_CFE_MAGIC_OFFSET ; 
 int /*<<< orphan*/  BCM963XX_CFE_VERSION_OFFSET ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,int,size_t*,void*) ; 
 int strncmp (char*,char*,int) ; 

__attribute__((used)) static int bcm63xx_detect_cfe(struct mtd_info *master)
{
	char buf[9];
	int ret;
	size_t retlen;

	ret = mtd_read(master, BCM963XX_CFE_VERSION_OFFSET, 5, &retlen,
		       (void *)buf);
	buf[retlen] = 0;

	if (ret)
		return ret;

	if (strncmp("cfe-v", buf, 5) == 0)
		return 0;

	/* very old CFE's do not have the cfe-v string, so check for magic */
	ret = mtd_read(master, BCM963XX_CFE_MAGIC_OFFSET, 8, &retlen,
		       (void *)buf);
	buf[retlen] = 0;

	return strncmp("CFE1CFE1", buf, 8);
}