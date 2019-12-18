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
typedef  int u32 ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int SHMEM_EEE_100M_ADV ; 
 int SHMEM_EEE_10G_ADV ; 
 int SHMEM_EEE_1G_ADV ; 

__attribute__((used)) static u32 bnx2x_eee_to_adv(u32 eee_adv)
{
	u32 modes = 0;

	if (eee_adv & SHMEM_EEE_100M_ADV)
		modes |= ADVERTISED_100baseT_Full;
	if (eee_adv & SHMEM_EEE_1G_ADV)
		modes |= ADVERTISED_1000baseT_Full;
	if (eee_adv & SHMEM_EEE_10G_ADV)
		modes |= ADVERTISED_10000baseT_Full;

	return modes;
}