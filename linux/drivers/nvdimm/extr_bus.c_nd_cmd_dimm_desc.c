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
struct nd_cmd_desc {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nd_cmd_desc const*) ; 
 struct nd_cmd_desc const* __nd_cmd_dimm_descs ; 

const struct nd_cmd_desc *nd_cmd_dimm_desc(int cmd)
{
	if (cmd < ARRAY_SIZE(__nd_cmd_dimm_descs))
		return &__nd_cmd_dimm_descs[cmd];
	return NULL;
}