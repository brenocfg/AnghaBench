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
struct tegra_ivc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * channel; } ;
struct tegra_bpmp {TYPE_1__ mbox; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_bpmp_ivc_notify(struct tegra_ivc *ivc, void *data)
{
	struct tegra_bpmp *bpmp = data;
	int err;

	if (WARN_ON(bpmp->mbox.channel == NULL))
		return;

	err = mbox_send_message(bpmp->mbox.channel, NULL);
	if (err < 0)
		return;

	mbox_client_txdone(bpmp->mbox.channel, 0);
}