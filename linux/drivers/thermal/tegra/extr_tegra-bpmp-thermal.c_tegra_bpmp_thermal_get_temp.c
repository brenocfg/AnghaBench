#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int temp; } ;
union mrq_thermal_bpmp_to_host_response {TYPE_5__ get_temp; } ;
struct tegra_bpmp_thermal_zone {TYPE_4__* tegra; int /*<<< orphan*/  idx; } ;
struct TYPE_8__ {int size; union mrq_thermal_bpmp_to_host_response* data; } ;
struct TYPE_7__ {int size; struct tegra_bpmp_message* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  zone; } ;
struct tegra_bpmp_message {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ get_temp; int /*<<< orphan*/  type; } ;
struct mrq_thermal_host_to_bpmp_request {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ get_temp; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_9__ {int /*<<< orphan*/  bpmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_THERMAL_GET_TEMP ; 
 int /*<<< orphan*/  MRQ_THERMAL ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (int /*<<< orphan*/ ,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_thermal_get_temp(void *data, int *out_temp)
{
	struct tegra_bpmp_thermal_zone *zone = data;
	struct mrq_thermal_host_to_bpmp_request req;
	union mrq_thermal_bpmp_to_host_response reply;
	struct tegra_bpmp_message msg;
	int err;

	memset(&req, 0, sizeof(req));
	req.type = CMD_THERMAL_GET_TEMP;
	req.get_temp.zone = zone->idx;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_THERMAL;
	msg.tx.data = &req;
	msg.tx.size = sizeof(req);
	msg.rx.data = &reply;
	msg.rx.size = sizeof(reply);

	err = tegra_bpmp_transfer(zone->tegra->bpmp, &msg);
	if (err)
		return err;

	*out_temp = reply.get_temp.temp;

	return 0;
}