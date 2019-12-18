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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ UBI_EC_MAGIC ; 
 int /*<<< orphan*/  mtd_is_bitflip (int) ; 
 int mtd_read (struct mtd_info*,size_t,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,int) ; 

__attribute__((used)) static const char *parser_trx_data_part_name(struct mtd_info *master,
					     size_t offset)
{
	uint32_t buf;
	size_t bytes_read;
	int err;

	err  = mtd_read(master, offset, sizeof(buf), &bytes_read,
			(uint8_t *)&buf);
	if (err && !mtd_is_bitflip(err)) {
		pr_err("mtd_read error while parsing (offset: 0x%zX): %d\n",
			offset, err);
		goto out_default;
	}

	if (buf == UBI_EC_MAGIC)
		return "ubi";

out_default:
	return "rootfs";
}