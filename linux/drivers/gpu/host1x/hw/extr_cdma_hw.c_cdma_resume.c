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
struct host1x_channel {int /*<<< orphan*/  id; } ;
struct host1x_cdma {int torndown; } ;
struct host1x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdma_hw_cmdproc_stop (struct host1x*,struct host1x_channel*,int) ; 
 int /*<<< orphan*/  cdma_timeout_restart (struct host1x_cdma*,int /*<<< orphan*/ ) ; 
 struct host1x_channel* cdma_to_channel (struct host1x_cdma*) ; 
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdma_resume(struct host1x_cdma *cdma, u32 getptr)
{
	struct host1x *host1x = cdma_to_host1x(cdma);
	struct host1x_channel *ch = cdma_to_channel(cdma);

	dev_dbg(host1x->dev,
		"resuming channel (id %u, DMAGET restart = 0x%x)\n",
		ch->id, getptr);

	cdma_hw_cmdproc_stop(host1x, ch, false);

	cdma->torndown = false;
	cdma_timeout_restart(cdma, getptr);
}