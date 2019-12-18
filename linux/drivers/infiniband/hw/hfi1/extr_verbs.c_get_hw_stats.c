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
typedef  int /*<<< orphan*/  u64 ;
struct rdma_hw_stats {int /*<<< orphan*/  value; } ;
struct ib_device {int dummy; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  hfi1_read_cntrs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hfi1_read_portcntrs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hfi1_sps_ints () ; 
 int /*<<< orphan*/  hfi1_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t num_dev_cntrs ; 
 int num_driver_cntrs ; 
 int num_port_cntrs ; 
 int /*<<< orphan*/  ppd_from_ibp (struct hfi1_ibport*) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_hw_stats(struct ib_device *ibdev, struct rdma_hw_stats *stats,
			u8 port, int index)
{
	u64 *values;
	int count;

	if (!port) {
		u64 *stats = (u64 *)&hfi1_stats;
		int i;

		hfi1_read_cntrs(dd_from_ibdev(ibdev), NULL, &values);
		values[num_dev_cntrs] = hfi1_sps_ints();
		for (i = 1; i < num_driver_cntrs; i++)
			values[num_dev_cntrs + i] = stats[i];
		count = num_dev_cntrs + num_driver_cntrs;
	} else {
		struct hfi1_ibport *ibp = to_iport(ibdev, port);

		hfi1_read_portcntrs(ppd_from_ibp(ibp), NULL, &values);
		count = num_port_cntrs;
	}

	memcpy(stats->value, values, count * sizeof(u64));
	return count;
}