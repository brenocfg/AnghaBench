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
typedef  int /*<<< orphan*/  u64 ;
struct intel_timeline {int dummy; } ;
struct __igt_sync {scalar_t__ expected; int /*<<< orphan*/  seqno; scalar_t__ set; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ __intel_timeline_sync_is_later (struct intel_timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __intel_timeline_sync_set (struct intel_timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (scalar_t__) ; 

__attribute__((used)) static int __igt_sync(struct intel_timeline *tl,
		      u64 ctx,
		      const struct __igt_sync *p,
		      const char *name)
{
	int ret;

	if (__intel_timeline_sync_is_later(tl, ctx, p->seqno) != p->expected) {
		pr_err("%s: %s(ctx=%llu, seqno=%u) expected passed %s but failed\n",
		       name, p->name, ctx, p->seqno, yesno(p->expected));
		return -EINVAL;
	}

	if (p->set) {
		ret = __intel_timeline_sync_set(tl, ctx, p->seqno);
		if (ret)
			return ret;
	}

	return 0;
}