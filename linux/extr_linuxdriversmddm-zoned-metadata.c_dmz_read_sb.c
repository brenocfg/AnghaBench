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
struct dmz_metadata {TYPE_2__* sb; } ;
struct TYPE_4__ {TYPE_1__* mblk; int /*<<< orphan*/  block; } ;
struct TYPE_3__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_READ ; 
 int dmz_rdwr_block (struct dmz_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmz_read_sb(struct dmz_metadata *zmd, unsigned int set)
{
	return dmz_rdwr_block(zmd, REQ_OP_READ, zmd->sb[set].block,
			      zmd->sb[set].mblk->page);
}