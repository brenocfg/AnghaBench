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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_timeline {int dummy; } ;
struct __igt_sync {char* member_0; int member_1; int member_2; int member_3; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ BIT_ULL (int) ; 
 int ENODEV ; 
 int INT_MAX ; 
 int UINT_MAX ; 
 int __igt_sync (struct intel_timeline*,scalar_t__,struct __igt_sync const*,char*) ; 
 int /*<<< orphan*/  mock_timeline_fini (struct intel_timeline*) ; 
 int /*<<< orphan*/  mock_timeline_init (struct intel_timeline*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igt_sync(void *arg)
{
	const struct __igt_sync pass[] = {
		{ "unset", 0, false, false },
		{ "new", 0, false, true },
		{ "0a", 0, true, true },
		{ "1a", 1, false, true },
		{ "1b", 1, true, true },
		{ "0b", 0, true, false },
		{ "2a", 2, false, true },
		{ "4", 4, false, true },
		{ "INT_MAX", INT_MAX, false, true },
		{ "INT_MAX-1", INT_MAX-1, true, false },
		{ "INT_MAX+1", (u32)INT_MAX+1, false, true },
		{ "INT_MAX", INT_MAX, true, false },
		{ "UINT_MAX", UINT_MAX, false, true },
		{ "wrap", 0, false, true },
		{ "unwrap", UINT_MAX, true, false },
		{},
	}, *p;
	struct intel_timeline tl;
	int order, offset;
	int ret = -ENODEV;

	mock_timeline_init(&tl, 0);
	for (p = pass; p->name; p++) {
		for (order = 1; order < 64; order++) {
			for (offset = -1; offset <= (order > 1); offset++) {
				u64 ctx = BIT_ULL(order) + offset;

				ret = __igt_sync(&tl, ctx, p, "1");
				if (ret)
					goto out;
			}
		}
	}
	mock_timeline_fini(&tl);

	mock_timeline_init(&tl, 0);
	for (order = 1; order < 64; order++) {
		for (offset = -1; offset <= (order > 1); offset++) {
			u64 ctx = BIT_ULL(order) + offset;

			for (p = pass; p->name; p++) {
				ret = __igt_sync(&tl, ctx, p, "2");
				if (ret)
					goto out;
			}
		}
	}

out:
	mock_timeline_fini(&tl);
	return ret;
}