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
struct timer_list {int dummy; } ;
struct ssi_protocol {struct hsi_client* cl; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ssi_protocol* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ssi_protocol* ssi ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 int /*<<< orphan*/  tx_wd ; 

__attribute__((used)) static void ssip_tx_wd(struct timer_list *t)
{
	struct ssi_protocol *ssi = from_timer(ssi, t, tx_wd);
	struct hsi_client *cl = ssi->cl;

	dev_err(&cl->device, "Watchdog triggered\n");
	ssip_error(cl);
}