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
struct bgx {int dummy; } ;

/* Variables and functions */
 struct bgx** bgx_vnic ; 
 int max_bgx_per_node ; 

__attribute__((used)) static struct bgx *get_bgx(int node, int bgx_idx)
{
	int idx = (node * max_bgx_per_node) + bgx_idx;

	return bgx_vnic[idx];
}