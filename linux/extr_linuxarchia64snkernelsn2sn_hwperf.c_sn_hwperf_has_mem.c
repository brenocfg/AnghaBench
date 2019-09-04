#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cnodeid_t ;
struct TYPE_2__ {scalar_t__ node_present_pages; } ;

/* Variables and functions */
 scalar_t__ MAX_NUMNODES ; 
 TYPE_1__* NODE_DATA (scalar_t__) ; 
 scalar_t__ node_online (scalar_t__) ; 

__attribute__((used)) static inline int sn_hwperf_has_mem(cnodeid_t node)
{
	return node < MAX_NUMNODES && node_online(node) && NODE_DATA(node)->node_present_pages;
}