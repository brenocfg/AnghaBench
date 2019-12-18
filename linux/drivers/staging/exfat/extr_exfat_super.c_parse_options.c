#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  substring_t ;
struct exfat_mount_options {int fs_fmask; int fs_dmask; int allow_utime; int codepage; char* iocharset; int casesensitive; int discard; void* errors; int /*<<< orphan*/  fs_gid; int /*<<< orphan*/  fs_uid; } ;
struct TYPE_4__ {TYPE_1__* fs; } ;
struct TYPE_3__ {int umask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 void* EXFAT_ERRORS_CONT ; 
 void* EXFAT_ERRORS_PANIC ; 
 void* EXFAT_ERRORS_RO ; 
 int /*<<< orphan*/  KGIDT_INIT (int) ; 
 int /*<<< orphan*/  KUIDT_INIT (int) ; 
 int MAX_OPT_ARGS ; 
#define  Opt_allow_utime 142 
#define  Opt_charset 141 
#define  Opt_codepage 140 
#define  Opt_debug 139 
#define  Opt_discard 138 
#define  Opt_dmask 137 
#define  Opt_err_cont 136 
#define  Opt_err_panic 135 
#define  Opt_err_ro 134 
#define  Opt_fmask 133 
#define  Opt_gid 132 
#define  Opt_namecase 131 
#define  Opt_uid 130 
#define  Opt_umask 129 
#define  Opt_utf8_hack 128 
 int U16_MAX ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int exfat_default_codepage ; 
 char* exfat_default_iocharset ; 
 int /*<<< orphan*/  exfat_tokens ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_octal (int /*<<< orphan*/ *,int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_options(char *options, int silent, int *debug,
			 struct exfat_mount_options *opts)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;
	char *iocharset;

	opts->fs_uid = current_uid();
	opts->fs_gid = current_gid();
	opts->fs_fmask = opts->fs_dmask = current->fs->umask;
	opts->allow_utime = U16_MAX;
	opts->codepage = exfat_default_codepage;
	opts->iocharset = exfat_default_iocharset;
	opts->casesensitive = 0;
	opts->errors = EXFAT_ERRORS_RO;
#ifdef CONFIG_EXFAT_DISCARD
	opts->discard = 0;
#endif
	*debug = 0;

	if (!options)
		goto out;

	while ((p = strsep(&options, ","))) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, exfat_tokens, args);
		switch (token) {
		case Opt_uid:
			if (match_int(&args[0], &option))
				return 0;
			opts->fs_uid = KUIDT_INIT(option);
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return 0;
			opts->fs_gid = KGIDT_INIT(option);
			break;
		case Opt_umask:
		case Opt_dmask:
		case Opt_fmask:
			if (match_octal(&args[0], &option))
				return 0;
			if (token != Opt_dmask)
				opts->fs_fmask = option;
			if (token != Opt_fmask)
				opts->fs_dmask = option;
			break;
		case Opt_allow_utime:
			if (match_octal(&args[0], &option))
				return 0;
			opts->allow_utime = option & 0022;
			break;
		case Opt_codepage:
			if (match_int(&args[0], &option))
				return 0;
			opts->codepage = option;
			break;
		case Opt_charset:
			if (opts->iocharset != exfat_default_iocharset)
				kfree(opts->iocharset);
			iocharset = match_strdup(&args[0]);
			if (!iocharset)
				return -ENOMEM;
			opts->iocharset = iocharset;
			break;
		case Opt_namecase:
			if (match_int(&args[0], &option))
				return 0;
			opts->casesensitive = option;
			break;
		case Opt_err_cont:
			opts->errors = EXFAT_ERRORS_CONT;
			break;
		case Opt_err_panic:
			opts->errors = EXFAT_ERRORS_PANIC;
			break;
		case Opt_err_ro:
			opts->errors = EXFAT_ERRORS_RO;
			break;
		case Opt_debug:
			*debug = 1;
			break;
#ifdef CONFIG_EXFAT_DISCARD
		case Opt_discard:
			opts->discard = 1;
			break;
#endif /* CONFIG_EXFAT_DISCARD */
		case Opt_utf8_hack:
			break;
		default:
			if (!silent)
				pr_err("[EXFAT] Unrecognized mount option %s or missing value\n",
				       p);
			return -EINVAL;
		}
	}

out:
	if (opts->allow_utime == U16_MAX)
		opts->allow_utime = ~opts->fs_dmask & 0022;

	return 0;
}