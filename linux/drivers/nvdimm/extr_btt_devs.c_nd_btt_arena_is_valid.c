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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct nd_gen_sb {int dummy; } ;
struct nd_btt {int /*<<< orphan*/  dev; TYPE_1__* ndns; } ;
struct btt_sb {int /*<<< orphan*/  flags; int /*<<< orphan*/  checksum; int /*<<< orphan*/  parent_uuid; int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  guid_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* BTT_SIG ; 
 int BTT_SIG_LEN ; 
 int IB_FLAG_ERROR_MASK ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  guid_is_null (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * nd_dev_to_uuid (int /*<<< orphan*/ *) ; 
 scalar_t__ nd_sb_checksum (struct nd_gen_sb*) ; 

bool nd_btt_arena_is_valid(struct nd_btt *nd_btt, struct btt_sb *super)
{
	const u8 *parent_uuid = nd_dev_to_uuid(&nd_btt->ndns->dev);
	u64 checksum;

	if (memcmp(super->signature, BTT_SIG, BTT_SIG_LEN) != 0)
		return false;

	if (!guid_is_null((guid_t *)&super->parent_uuid))
		if (memcmp(super->parent_uuid, parent_uuid, 16) != 0)
			return false;

	checksum = le64_to_cpu(super->checksum);
	super->checksum = 0;
	if (checksum != nd_sb_checksum((struct nd_gen_sb *) super))
		return false;
	super->checksum = cpu_to_le64(checksum);

	/* TODO: figure out action for this */
	if ((le32_to_cpu(super->flags) & IB_FLAG_ERROR_MASK) != 0)
		dev_info(&nd_btt->dev, "Found arena with an error flag\n");

	return true;
}