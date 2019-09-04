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
struct mtd_info {struct map_info* priv; } ;
struct map_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  lpdd2_nvm_mutex ; 
 int /*<<< orphan*/  map_copy_from (struct map_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpddr2_nvm_read(struct mtd_info *mtd, loff_t start_add,
				size_t len, size_t *retlen, u_char *buf)
{
	struct map_info *map = mtd->priv;

	mutex_lock(&lpdd2_nvm_mutex);

	*retlen = len;

	map_copy_from(map, buf, start_add, *retlen);

	mutex_unlock(&lpdd2_nvm_mutex);
	return 0;
}