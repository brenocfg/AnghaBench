#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_6__ {int /*<<< orphan*/  callback; TYPE_1__ ccw; } ;
struct raw3270 {scalar_t__ state; TYPE_2__ init_readmod; int /*<<< orphan*/  init_view; TYPE_2__ init_data; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 scalar_t__ RAW3270_STATE_READMOD ; 
 scalar_t__ RAW3270_STATE_W4ATTN ; 
 int /*<<< orphan*/  TC_READMOD ; 
 scalar_t__ __pa (TYPE_2__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw3270_read_modified_cb ; 
 int /*<<< orphan*/  raw3270_start_irq (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
raw3270_read_modified(struct raw3270 *rp)
{
	if (rp->state != RAW3270_STATE_W4ATTN)
		return;
	/* Use 'read modified' to get the result of a read partition. */
	memset(&rp->init_readmod, 0, sizeof(rp->init_readmod));
	memset(&rp->init_data, 0, sizeof(rp->init_data));
	rp->init_readmod.ccw.cmd_code = TC_READMOD;
	rp->init_readmod.ccw.flags = CCW_FLAG_SLI;
	rp->init_readmod.ccw.count = sizeof(rp->init_data);
	rp->init_readmod.ccw.cda = (__u32) __pa(rp->init_data);
	rp->init_readmod.callback = raw3270_read_modified_cb;
	rp->state = RAW3270_STATE_READMOD;
	raw3270_start_irq(&rp->init_view, &rp->init_readmod);
}