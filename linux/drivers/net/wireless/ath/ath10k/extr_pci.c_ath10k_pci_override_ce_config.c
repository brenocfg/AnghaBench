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
struct ce_pipe_config {void* nbytes_max; void* pipedir; } ;
struct ce_attr {scalar_t__ dest_nentries; scalar_t__ src_sz_max; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {void* pipenum; } ;

/* Variables and functions */
 int PIPEDIR_OUT ; 
 void* __cpu_to_le32 (int) ; 
 struct ce_attr* host_ce_config_wlan ; 
 struct ce_pipe_config* target_ce_config_wlan ; 
 TYPE_1__* target_service_to_ce_map_wlan ; 

__attribute__((used)) static void ath10k_pci_override_ce_config(struct ath10k *ar)
{
	struct ce_attr *attr;
	struct ce_pipe_config *config;

	/* For QCA6174 we're overriding the Copy Engine 5 configuration,
	 * since it is currently used for other feature.
	 */

	/* Override Host's Copy Engine 5 configuration */
	attr = &host_ce_config_wlan[5];
	attr->src_sz_max = 0;
	attr->dest_nentries = 0;

	/* Override Target firmware's Copy Engine configuration */
	config = &target_ce_config_wlan[5];
	config->pipedir = __cpu_to_le32(PIPEDIR_OUT);
	config->nbytes_max = __cpu_to_le32(2048);

	/* Map from service/endpoint to Copy Engine */
	target_service_to_ce_map_wlan[15].pipenum = __cpu_to_le32(1);
}