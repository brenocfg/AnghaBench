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
struct tb_cfg_header {int route_lo; scalar_t__ route_hi; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 tb_cfg_get_route(const struct tb_cfg_header *header)
{
	return (u64) header->route_hi << 32 | header->route_lo;
}