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
struct qlcnic_adapter {int /*<<< orphan*/  max_rds_rings; int /*<<< orphan*/  num_txd; int /*<<< orphan*/  max_jumbo_rxd; int /*<<< orphan*/  num_jumbo_rxd; int /*<<< orphan*/  max_rxd; int /*<<< orphan*/  num_rxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMD_DESCRIPTORS ; 
 int /*<<< orphan*/  MAX_JUMBO_RCV_DESCRIPTORS_10G ; 
 int /*<<< orphan*/  MAX_RCV_DESCRIPTORS_10G ; 
 int /*<<< orphan*/  MAX_RDS_RINGS ; 
 int /*<<< orphan*/  QLC_DEFAULT_JUMBO_RCV_DESCRIPTORS_SRIOV_VF ; 
 int /*<<< orphan*/  QLC_DEFAULT_RCV_DESCRIPTORS_SRIOV_VF ; 

__attribute__((used)) static void qlcnic_sriov_vf_cfg_buff_desc(struct qlcnic_adapter *adapter)
{
	adapter->num_rxd = QLC_DEFAULT_RCV_DESCRIPTORS_SRIOV_VF;
	adapter->max_rxd = MAX_RCV_DESCRIPTORS_10G;
	adapter->num_jumbo_rxd = QLC_DEFAULT_JUMBO_RCV_DESCRIPTORS_SRIOV_VF;
	adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	adapter->num_txd = MAX_CMD_DESCRIPTORS;
	adapter->max_rds_rings = MAX_RDS_RINGS;
}