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
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int ETH_ALEN ; 

__attribute__((used)) static u64 ibmveth_encode_mac_addr(u8 *mac)
{
	int i;
	u64 encoded = 0;

	for (i = 0; i < ETH_ALEN; i++)
		encoded = (encoded << 8) | mac[i];

	return encoded;
}