#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp_thermal_zone {TYPE_3__* tegra; int /*<<< orphan*/  idx; } ;
struct TYPE_5__ {int size; struct tegra_bpmp_message* data; } ;
struct TYPE_4__ {int enabled; int low; int high; int /*<<< orphan*/  zone; } ;
struct tegra_bpmp_message {TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ set_trip; int /*<<< orphan*/  type; } ;
struct mrq_thermal_host_to_bpmp_request {TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ set_trip; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_6__ {int /*<<< orphan*/  bpmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_THERMAL_SET_TRIP ; 
 int /*<<< orphan*/  MRQ_THERMAL ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (int /*<<< orphan*/ ,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_thermal_set_trips(void *data, int low, int high)
{
	struct tegra_bpmp_thermal_zone *zone = data;
	struct mrq_thermal_host_to_bpmp_request req;
	struct tegra_bpmp_message msg;

	memset(&req, 0, sizeof(req));
	req.type = CMD_THERMAL_SET_TRIP;
	req.set_trip.zone = zone->idx;
	req.set_trip.enabled = true;
	req.set_trip.low = low;
	req.set_trip.high = high;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_THERMAL;
	msg.tx.data = &req;
	msg.tx.size = sizeof(req);

	return tegra_bpmp_transfer(zone->tegra->bpmp, &msg);
}