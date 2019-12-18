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
struct ubi_volume_desc {int dummy; } ;
struct ubi_volume {int name_len; int /*<<< orphan*/  name; } ;
struct ubi_device {int vtbl_slots; int /*<<< orphan*/  volumes_lock; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct ubi_volume_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int UBI_MAX_DEVICES ; 
 int UBI_VOL_NAME_MAX ; 
 int /*<<< orphan*/  dbg_gen (char*,int,char const*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strnlen (char const*,int) ; 
 struct ubi_device* ubi_get_device (int) ; 
 struct ubi_volume_desc* ubi_open_volume (int,int,int) ; 
 int /*<<< orphan*/  ubi_put_device (struct ubi_device*) ; 

struct ubi_volume_desc *ubi_open_volume_nm(int ubi_num, const char *name,
					   int mode)
{
	int i, vol_id = -1, len;
	struct ubi_device *ubi;
	struct ubi_volume_desc *ret;

	dbg_gen("open device %d, volume %s, mode %d", ubi_num, name, mode);

	if (!name)
		return ERR_PTR(-EINVAL);

	len = strnlen(name, UBI_VOL_NAME_MAX + 1);
	if (len > UBI_VOL_NAME_MAX)
		return ERR_PTR(-EINVAL);

	if (ubi_num < 0 || ubi_num >= UBI_MAX_DEVICES)
		return ERR_PTR(-EINVAL);

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		return ERR_PTR(-ENODEV);

	spin_lock(&ubi->volumes_lock);
	/* Walk all volumes of this UBI device */
	for (i = 0; i < ubi->vtbl_slots; i++) {
		struct ubi_volume *vol = ubi->volumes[i];

		if (vol && len == vol->name_len && !strcmp(name, vol->name)) {
			vol_id = i;
			break;
		}
	}
	spin_unlock(&ubi->volumes_lock);

	if (vol_id >= 0)
		ret = ubi_open_volume(ubi_num, vol_id, mode);
	else
		ret = ERR_PTR(-ENODEV);

	/*
	 * We should put the UBI device even in case of success, because
	 * 'ubi_open_volume()' took a reference as well.
	 */
	ubi_put_device(ubi);
	return ret;
}