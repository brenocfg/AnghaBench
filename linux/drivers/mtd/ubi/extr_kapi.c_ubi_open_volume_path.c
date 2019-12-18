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
struct path {int dummy; } ;
struct kstat {int /*<<< orphan*/  rdev; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int EINVAL ; 
 int ENODEV ; 
 struct ubi_volume_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATX_TYPE ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_gen (char*,char const*,int) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int ubi_major2num (int /*<<< orphan*/ ) ; 
 struct ubi_volume_desc* ubi_open_volume (int,int,int) ; 
 int vfs_getattr (struct path*,struct kstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ubi_volume_desc *ubi_open_volume_path(const char *pathname, int mode)
{
	int error, ubi_num, vol_id;
	struct path path;
	struct kstat stat;

	dbg_gen("open volume %s, mode %d", pathname, mode);

	if (!pathname || !*pathname)
		return ERR_PTR(-EINVAL);

	error = kern_path(pathname, LOOKUP_FOLLOW, &path);
	if (error)
		return ERR_PTR(error);

	error = vfs_getattr(&path, &stat, STATX_TYPE, AT_STATX_SYNC_AS_STAT);
	path_put(&path);
	if (error)
		return ERR_PTR(error);

	if (!S_ISCHR(stat.mode))
		return ERR_PTR(-EINVAL);

	ubi_num = ubi_major2num(MAJOR(stat.rdev));
	vol_id = MINOR(stat.rdev) - 1;

	if (vol_id >= 0 && ubi_num >= 0)
		return ubi_open_volume(ubi_num, vol_id, mode);
	return ERR_PTR(-ENODEV);
}