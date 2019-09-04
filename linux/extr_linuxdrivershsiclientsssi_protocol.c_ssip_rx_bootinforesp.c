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
struct ssi_protocol {scalar_t__ main_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_wd; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 scalar_t__ SSIP_DATA_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ SSIP_LOCAL_VERID ; 
 int /*<<< orphan*/  SSIP_WDTOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssip_rx_bootinforesp(struct hsi_client *cl, u32 cmd)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);

	if (SSIP_DATA_VERSION(cmd) != SSIP_LOCAL_VERID)
		dev_warn(&cl->device, "boot info resp verid mismatch\n");

	spin_lock_bh(&ssi->lock);
	if (ssi->main_state != ACTIVE)
		/* Use tx_wd as a boot watchdog in non ACTIVE state */
		mod_timer(&ssi->tx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
	else
		dev_dbg(&cl->device, "boot info resp ignored M(%d)\n",
							ssi->main_state);
	spin_unlock_bh(&ssi->lock);
}