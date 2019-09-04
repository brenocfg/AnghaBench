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
typedef  size_t u_long ;
typedef  int u_char ;
struct pcm_int_data {int bus_width; } ;
struct mtd_info {scalar_t__ writesize; struct map_info* priv; } ;
struct map_info {struct pcm_int_data* fldrv_priv; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (size_t,scalar_t__) ; 
 int /*<<< orphan*/  LPDDR2_NVM_BUF_OVERWRITE ; 
 int /*<<< orphan*/  LPDDR2_NVM_SW_OVERWRITE ; 
 int /*<<< orphan*/  lpdd2_nvm_mutex ; 
 int lpddr2_nvm_do_op (struct map_info*,int /*<<< orphan*/ ,int,size_t,size_t,int*) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ow_disable (struct map_info*) ; 
 int /*<<< orphan*/  ow_enable (struct map_info*) ; 

__attribute__((used)) static int lpddr2_nvm_write(struct mtd_info *mtd, loff_t start_add,
				size_t len, size_t *retlen, const u_char *buf)
{
	struct map_info *map = mtd->priv;
	struct pcm_int_data *pcm_data = map->fldrv_priv;
	u_long add, current_len, tot_len, target_len, my_data;
	u_char *write_buf = (u_char *)buf;
	int ret = 0;

	mutex_lock(&lpdd2_nvm_mutex);

	ow_enable(map);

	/* Set start value for the variables */
	add = start_add;
	target_len = len;
	tot_len = 0;

	while (tot_len < target_len) {
		if (!(IS_ALIGNED(add, mtd->writesize))) { /* do sw program */
			my_data = write_buf[tot_len];
			my_data += (write_buf[tot_len+1]) << 8;
			if (pcm_data->bus_width == 0x0004) {/* 2x16 devices */
				my_data += (write_buf[tot_len+2]) << 16;
				my_data += (write_buf[tot_len+3]) << 24;
			}
			ret = lpddr2_nvm_do_op(map, LPDDR2_NVM_SW_OVERWRITE,
				my_data, add, 0x00, NULL);
			if (ret)
				goto out;

			add += pcm_data->bus_width;
			tot_len += pcm_data->bus_width;
		} else {		/* do buffer program */
			current_len = min(target_len - tot_len,
				(u_long) mtd->writesize);
			ret = lpddr2_nvm_do_op(map, LPDDR2_NVM_BUF_OVERWRITE,
				0x00, add, current_len, write_buf + tot_len);
			if (ret)
				goto out;

			add += current_len;
			tot_len += current_len;
		}
	}

out:
	*retlen = tot_len;
	ow_disable(map);
	mutex_unlock(&lpdd2_nvm_mutex);
	return ret;
}