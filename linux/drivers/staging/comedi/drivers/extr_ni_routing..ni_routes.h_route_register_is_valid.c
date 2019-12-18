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
struct ni_route_tables {int dummy; } ;

/* Variables and functions */
 scalar_t__ ni_find_route_source (int /*<<< orphan*/  const,int const,struct ni_route_tables const*) ; 

__attribute__((used)) static inline bool route_register_is_valid(const u8 src_sel_reg_value,
					   const int dest,
					   const struct ni_route_tables *tables)
{
	return ni_find_route_source(src_sel_reg_value, dest, tables) >= 0;
}