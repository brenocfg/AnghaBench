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
typedef  unsigned int u64 ;
struct throtl_grp {int dummy; } ;
struct kernfs_open_file {int dummy; } ;
struct blkg_conf_ctx {int /*<<< orphan*/  blkg; int /*<<< orphan*/  body; } ;
struct blkcg {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int private; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int U64_MAX ; 
 int /*<<< orphan*/  blkcg_policy_throtl ; 
 int /*<<< orphan*/  blkg_conf_finish (struct blkg_conf_ctx*) ; 
 int blkg_conf_prep (struct blkcg*,int /*<<< orphan*/ *,char*,struct blkg_conf_ctx*) ; 
 struct throtl_grp* blkg_to_tg (int /*<<< orphan*/ ) ; 
 struct blkcg* css_to_blkcg (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  tg_conf_updated (struct throtl_grp*,int) ; 

__attribute__((used)) static ssize_t tg_set_conf(struct kernfs_open_file *of,
			   char *buf, size_t nbytes, loff_t off, bool is_u64)
{
	struct blkcg *blkcg = css_to_blkcg(of_css(of));
	struct blkg_conf_ctx ctx;
	struct throtl_grp *tg;
	int ret;
	u64 v;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_throtl, buf, &ctx);
	if (ret)
		return ret;

	ret = -EINVAL;
	if (sscanf(ctx.body, "%llu", &v) != 1)
		goto out_finish;
	if (!v)
		v = U64_MAX;

	tg = blkg_to_tg(ctx.blkg);

	if (is_u64)
		*(u64 *)((void *)tg + of_cft(of)->private) = v;
	else
		*(unsigned int *)((void *)tg + of_cft(of)->private) = v;

	tg_conf_updated(tg, false);
	ret = 0;
out_finish:
	blkg_conf_finish(&ctx);
	return ret ?: nbytes;
}