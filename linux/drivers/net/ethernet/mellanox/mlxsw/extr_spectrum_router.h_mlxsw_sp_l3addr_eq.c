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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (union mlxsw_sp_l3addr const*,union mlxsw_sp_l3addr const*,int) ; 

__attribute__((used)) static inline bool mlxsw_sp_l3addr_eq(const union mlxsw_sp_l3addr *addr1,
				      const union mlxsw_sp_l3addr *addr2)
{
	return !memcmp(addr1, addr2, sizeof(*addr1));
}