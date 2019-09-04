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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  mac_lo_be ;
typedef  int /*<<< orphan*/  mac_hi_be ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bnx2x_set_mac_buf(u8 *mac_buf, u32 mac_lo, u16 mac_hi)
{
	__be16 mac_hi_be = cpu_to_be16(mac_hi);
	__be32 mac_lo_be = cpu_to_be32(mac_lo);
	memcpy(mac_buf, &mac_hi_be, sizeof(mac_hi_be));
	memcpy(mac_buf + sizeof(mac_hi_be), &mac_lo_be, sizeof(mac_lo_be));
}