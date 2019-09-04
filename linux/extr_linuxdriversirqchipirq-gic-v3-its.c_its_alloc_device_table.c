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
typedef  int /*<<< orphan*/  u32 ;
struct its_node {scalar_t__ device_ids; } ;
struct its_baser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_BASER_TYPE_DEVICE ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 int its_alloc_table_entry (struct its_baser*,int /*<<< orphan*/ ) ; 
 struct its_baser* its_get_baser (struct its_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool its_alloc_device_table(struct its_node *its, u32 dev_id)
{
	struct its_baser *baser;

	baser = its_get_baser(its, GITS_BASER_TYPE_DEVICE);

	/* Don't allow device id that exceeds ITS hardware limit */
	if (!baser)
		return (ilog2(dev_id) < its->device_ids);

	return its_alloc_table_entry(baser, dev_id);
}