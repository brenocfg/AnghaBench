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
struct ni_route_tables {int dummy; } ;

/* Variables and functions */
 int ni_get_reg_value_roffs (int const,int const,struct ni_route_tables const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ni_get_reg_value(const int src, const int dest,
				   const struct ni_route_tables *tables)
{
	return ni_get_reg_value_roffs(src, dest, tables, 0);
}