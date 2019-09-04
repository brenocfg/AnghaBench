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
struct page {int dummy; } ;
struct flex_array {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  addr_conv_t ;

/* Variables and functions */
 struct flex_array* flex_array_alloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flex_array_free (struct flex_array*) ; 
 scalar_t__ flex_array_prealloc (struct flex_array*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct flex_array *scribble_alloc(int num, int cnt, gfp_t flags)
{
	struct flex_array *ret;
	size_t len;

	len = sizeof(struct page *) * (num+2) + sizeof(addr_conv_t) * (num+2);
	ret = flex_array_alloc(len, cnt, flags);
	if (!ret)
		return NULL;
	/* always prealloc all elements, so no locking is required */
	if (flex_array_prealloc(ret, 0, cnt, flags)) {
		flex_array_free(ret);
		return NULL;
	}
	return ret;
}