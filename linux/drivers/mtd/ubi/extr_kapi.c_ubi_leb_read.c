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
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int vol_id; scalar_t__ vol_type; int corrupted; struct ubi_device* ubi; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ UBI_STATIC_VOLUME ; 
 int /*<<< orphan*/  dbg_gen (char*,int,int,int,int) ; 
 int leb_read_sanity_check (struct ubi_volume_desc*,int,int,int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int ubi_eba_read_leb (struct ubi_device*,struct ubi_volume*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int) ; 

int ubi_leb_read(struct ubi_volume_desc *desc, int lnum, char *buf, int offset,
		 int len, int check)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;
	int err, vol_id = vol->vol_id;

	dbg_gen("read %d bytes from LEB %d:%d:%d", len, vol_id, lnum, offset);

	err = leb_read_sanity_check(desc, lnum, offset, len);
	if (err < 0)
		return err;

	if (len == 0)
		return 0;

	err = ubi_eba_read_leb(ubi, vol, lnum, buf, offset, len, check);
	if (err && mtd_is_eccerr(err) && vol->vol_type == UBI_STATIC_VOLUME) {
		ubi_warn(ubi, "mark volume %d as corrupted", vol_id);
		vol->corrupted = 1;
	}

	return err;
}