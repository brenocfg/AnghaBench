#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fs_parse_result {int uint_32; int /*<<< orphan*/  boolean; } ;
struct fs_parameter {int /*<<< orphan*/  key; } ;
struct fs_context {struct ffs_sb_fill_data* fs_private; } ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ffs_sb_fill_data {int root_mode; TYPE_1__ perms; int /*<<< orphan*/  no_disconnect; } ;

/* Variables and functions */
 int ENOPARAM ; 
 int /*<<< orphan*/  ENTER () ; 
#define  Opt_fmode 133 
#define  Opt_gid 132 
#define  Opt_mode 131 
#define  Opt_no_disconnect 130 
#define  Opt_rmode 129 
#define  Opt_uid 128 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  ffs_fs_fs_parameters ; 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int invalf (struct fs_context*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffs_fs_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct ffs_sb_fill_data *data = fc->fs_private;
	struct fs_parse_result result;
	int opt;

	ENTER();

	opt = fs_parse(fc, &ffs_fs_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case Opt_no_disconnect:
		data->no_disconnect = result.boolean;
		break;
	case Opt_rmode:
		data->root_mode  = (result.uint_32 & 0555) | S_IFDIR;
		break;
	case Opt_fmode:
		data->perms.mode = (result.uint_32 & 0666) | S_IFREG;
		break;
	case Opt_mode:
		data->root_mode  = (result.uint_32 & 0555) | S_IFDIR;
		data->perms.mode = (result.uint_32 & 0666) | S_IFREG;
		break;

	case Opt_uid:
		data->perms.uid = make_kuid(current_user_ns(), result.uint_32);
		if (!uid_valid(data->perms.uid))
			goto unmapped_value;
		break;
	case Opt_gid:
		data->perms.gid = make_kgid(current_user_ns(), result.uint_32);
		if (!gid_valid(data->perms.gid))
			goto unmapped_value;
		break;

	default:
		return -ENOPARAM;
	}

	return 0;

unmapped_value:
	return invalf(fc, "%s: unmapped value: %u", param->key, result.uint_32);
}