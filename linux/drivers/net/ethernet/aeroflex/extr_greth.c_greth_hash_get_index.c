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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int ether_crc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 greth_hash_get_index(__u8 *addr)
{
	return (ether_crc(6, addr)) & 0x3F;
}