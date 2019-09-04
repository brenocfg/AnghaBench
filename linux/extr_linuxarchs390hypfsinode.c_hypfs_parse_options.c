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
typedef  int /*<<< orphan*/  substring_t ;
struct super_block {struct hypfs_sb_info* s_fs_info; } ;
struct hypfs_sb_info {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypfs_tokens ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  opt_err 130 
#define  opt_gid 129 
#define  opt_uid 128 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hypfs_parse_options(char *options, struct super_block *sb)
{
	char *str;
	substring_t args[MAX_OPT_ARGS];
	kuid_t uid;
	kgid_t gid;

	if (!options)
		return 0;
	while ((str = strsep(&options, ",")) != NULL) {
		int token, option;
		struct hypfs_sb_info *hypfs_info = sb->s_fs_info;

		if (!*str)
			continue;
		token = match_token(str, hypfs_tokens, args);
		switch (token) {
		case opt_uid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uid))
				return -EINVAL;
			hypfs_info->uid = uid;
			break;
		case opt_gid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(gid))
				return -EINVAL;
			hypfs_info->gid = gid;
			break;
		case opt_err:
		default:
			pr_err("%s is not a valid mount option\n", str);
			return -EINVAL;
		}
	}
	return 0;
}