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
typedef  int /*<<< orphan*/  u32 ;
struct tb_property_dir {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t __tb_property_format_dir (struct tb_property_dir const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t tb_property_dir_length (struct tb_property_dir const*,int,size_t*) ; 

ssize_t tb_property_format_dir(const struct tb_property_dir *dir, u32 *block,
			       size_t block_len)
{
	ssize_t ret;

	if (!block) {
		size_t dir_len, data_len = 0;

		dir_len = tb_property_dir_length(dir, true, &data_len);
		return dir_len + data_len;
	}

	ret = __tb_property_format_dir(dir, block, 0, block_len);
	return ret < 0 ? ret : 0;
}