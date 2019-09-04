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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int RSS_HASH_KEY_SIZE ; 

__attribute__((used)) static u32 nicvf_get_rxfh_key_size(struct net_device *netdev)
{
	return RSS_HASH_KEY_SIZE * sizeof(u64);
}