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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  substring_t ;
struct fcloop_ctrl_options {int mask; int roles; int fcaddr; void* lpwwpn; void* lpwwnn; void* wwpn; void* wwnn; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  NVMF_OPT_FCADDR 133 
#define  NVMF_OPT_LPWWNN 132 
#define  NVMF_OPT_LPWWPN 131 
#define  NVMF_OPT_ROLES 130 
#define  NVMF_OPT_WWNN 129 
#define  NVMF_OPT_WWPN 128 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_hex (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_u64 (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  opt_tokens ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
fcloop_parse_options(struct fcloop_ctrl_options *opts,
		const char *buf)
{
	substring_t args[MAX_OPT_ARGS];
	char *options, *o, *p;
	int token, ret = 0;
	u64 token64;

	options = o = kstrdup(buf, GFP_KERNEL);
	if (!options)
		return -ENOMEM;

	while ((p = strsep(&o, ",\n")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, opt_tokens, args);
		opts->mask |= token;
		switch (token) {
		case NVMF_OPT_WWNN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->wwnn = token64;
			break;
		case NVMF_OPT_WWPN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->wwpn = token64;
			break;
		case NVMF_OPT_ROLES:
			if (match_int(args, &token)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->roles = token;
			break;
		case NVMF_OPT_FCADDR:
			if (match_hex(args, &token)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->fcaddr = token;
			break;
		case NVMF_OPT_LPWWNN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->lpwwnn = token64;
			break;
		case NVMF_OPT_LPWWPN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			opts->lpwwpn = token64;
			break;
		default:
			pr_warn("unknown parameter or missing value '%s'\n", p);
			ret = -EINVAL;
			goto out_free_options;
		}
	}

out_free_options:
	kfree(options);
	return ret;
}