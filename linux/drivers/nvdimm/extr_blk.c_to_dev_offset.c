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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct nd_namespace_blk {int num_resources; TYPE_1__ common; TYPE_2__** res; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_4__ {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ resource_size (TYPE_2__*) ; 

__attribute__((used)) static resource_size_t to_dev_offset(struct nd_namespace_blk *nsblk,
				resource_size_t ns_offset, unsigned int len)
{
	int i;

	for (i = 0; i < nsblk->num_resources; i++) {
		if (ns_offset < resource_size(nsblk->res[i])) {
			if (ns_offset + len > resource_size(nsblk->res[i])) {
				dev_WARN_ONCE(&nsblk->common.dev, 1,
					"illegal request\n");
				return SIZE_MAX;
			}
			return nsblk->res[i]->start + ns_offset;
		}
		ns_offset -= resource_size(nsblk->res[i]);
	}

	dev_WARN_ONCE(&nsblk->common.dev, 1, "request out of range\n");
	return SIZE_MAX;
}