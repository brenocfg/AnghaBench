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
struct ib_mad_private {size_t mad_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct ib_mad_private* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_mad_private *alloc_mad_private(size_t mad_size, gfp_t flags)
{
	size_t size = sizeof(struct ib_mad_private) + mad_size;
	struct ib_mad_private *ret = kzalloc(size, flags);

	if (ret)
		ret->mad_size = mad_size;

	return ret;
}