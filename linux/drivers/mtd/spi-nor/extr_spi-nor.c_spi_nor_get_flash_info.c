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
struct spi_nor {int /*<<< orphan*/  dev; } ;
struct flash_info {int /*<<< orphan*/  name; scalar_t__ id_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct flash_info const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct flash_info const*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct flash_info const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flash_info* spi_nor_match_id (char const*) ; 
 struct flash_info* spi_nor_read_id (struct spi_nor*) ; 

__attribute__((used)) static const struct flash_info *spi_nor_get_flash_info(struct spi_nor *nor,
						       const char *name)
{
	const struct flash_info *info = NULL;

	if (name)
		info = spi_nor_match_id(name);
	/* Try to auto-detect if chip name wasn't specified or not found */
	if (!info)
		info = spi_nor_read_id(nor);
	if (IS_ERR_OR_NULL(info))
		return ERR_PTR(-ENOENT);

	/*
	 * If caller has specified name of flash model that can normally be
	 * detected using JEDEC, let's verify it.
	 */
	if (name && info->id_len) {
		const struct flash_info *jinfo;

		jinfo = spi_nor_read_id(nor);
		if (IS_ERR(jinfo)) {
			return jinfo;
		} else if (jinfo != info) {
			/*
			 * JEDEC knows better, so overwrite platform ID. We
			 * can't trust partitions any longer, but we'll let
			 * mtd apply them anyway, since some partitions may be
			 * marked read-only, and we don't want to lose that
			 * information, even if it's not 100% accurate.
			 */
			dev_warn(nor->dev, "found %s, expected %s\n",
				 jinfo->name, info->name);
			info = jinfo;
		}
	}

	return info;
}