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
struct alx_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_STAD0 ; 
 int /*<<< orphan*/  ALX_STAD1 ; 
 int /*<<< orphan*/  alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool alx_read_macaddr(struct alx_hw *hw, u8 *addr)
{
	u32 mac0, mac1;

	mac0 = alx_read_mem32(hw, ALX_STAD0);
	mac1 = alx_read_mem32(hw, ALX_STAD1);

	/* addr should be big-endian */
	put_unaligned(cpu_to_be32(mac0), (__be32 *)(addr + 2));
	put_unaligned(cpu_to_be16(mac1), (__be16 *)addr);

	return is_valid_ether_addr(addr);
}