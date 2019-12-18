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
 scalar_t__ ni_route_to_register (int const,int const,struct ni_route_tables const*) ; 

__attribute__((used)) static inline bool route_is_valid(const int src, const int dest,
				  const struct ni_route_tables *tables)
{
	return ni_route_to_register(src, dest, tables) >= 0;
}