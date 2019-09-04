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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40iw_ipv4_is_loopback(u32 loc_addr, u32 rem_addr)
{
	return ipv4_is_loopback(htonl(rem_addr)) || (loc_addr == rem_addr);
}