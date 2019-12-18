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
typedef  int /*<<< orphan*/  u8 ;
struct nd_namespace_pmem {int /*<<< orphan*/  const* uuid; } ;
struct nd_namespace_blk {int /*<<< orphan*/  const* uuid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 

const u8 *nd_dev_to_uuid(struct device *dev)
{
	static const u8 null_uuid[16];

	if (!dev)
		return null_uuid;

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		return nspm->uuid;
	} else if (is_namespace_blk(dev)) {
		struct nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		return nsblk->uuid;
	} else
		return null_uuid;
}