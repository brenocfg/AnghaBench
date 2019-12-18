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
typedef  int u64 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx4_en_u64_to_mac(unsigned char dst_mac[ETH_ALEN + 2], u64 src_mac)
{
	int i;
	for (i = ETH_ALEN - 1; i >= 0; --i) {
		dst_mac[i] = src_mac & 0xff;
		src_mac >>= 8;
	}
	memset(&dst_mac[ETH_ALEN], 0, 2);
}