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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {scalar_t__ priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int ram_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	memcpy((char *)mtd->priv + to, buf, len);
	*retlen = len;
	return 0;
}