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

/* Variables and functions */
 int MAX_NUMNODES ; 
 int first_online_node ; 
 int next_online_node (int) ; 

__attribute__((used)) static inline int mtip_get_next_rr_node(void)
{
	static int next_node = -1;

	if (next_node == -1) {
		next_node = first_online_node;
		return next_node;
	}

	next_node = next_online_node(next_node);
	if (next_node == MAX_NUMNODES)
		next_node = first_online_node;
	return next_node;
}