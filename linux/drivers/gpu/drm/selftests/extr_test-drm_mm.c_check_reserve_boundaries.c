#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct boundary   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct drm_mm_node {int dummy; } ;
struct drm_mm {int dummy; } ;
struct boundary {unsigned int start; unsigned int size; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__ const*) ; 
 TYPE_1__ const B (unsigned int,int) ; 
 int /*<<< orphan*/  expect_reserve_fail (struct drm_mm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_node (struct drm_mm_node*,unsigned int,unsigned int) ; 

__attribute__((used)) static bool check_reserve_boundaries(struct drm_mm *mm,
				     unsigned int count,
				     u64 size)
{
	const struct boundary {
		u64 start, size;
		const char *name;
	} boundaries[] = {
#define B(st, sz) { (st), (sz), "{ " #st ", " #sz "}" }
		B(0, 0),
		B(-size, 0),
		B(size, 0),
		B(size * count, 0),
		B(-size, size),
		B(-size, -size),
		B(-size, 2*size),
		B(0, -size),
		B(size, -size),
		B(count*size, size),
		B(count*size, -size),
		B(count*size, count*size),
		B(count*size, -count*size),
		B(count*size, -(count+1)*size),
		B((count+1)*size, size),
		B((count+1)*size, -size),
		B((count+1)*size, -2*size),
#undef B
	};
	struct drm_mm_node tmp = {};
	int n;

	for (n = 0; n < ARRAY_SIZE(boundaries); n++) {
		if (!expect_reserve_fail(mm,
					 set_node(&tmp,
						  boundaries[n].start,
						  boundaries[n].size))) {
			pr_err("boundary[%d:%s] failed, count=%u, size=%lld\n",
			       n, boundaries[n].name, count, size);
			return false;
		}
	}

	return true;
}