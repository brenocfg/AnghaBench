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
typedef  scalar_t__ u32 ;
struct intel_gvt {int dummy; } ;
struct cmd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ INVALID_OP ; 
 struct cmd_info const* find_cmd_entry (struct intel_gvt*,scalar_t__,int) ; 
 scalar_t__ get_opcode (scalar_t__,int) ; 

__attribute__((used)) static inline const struct cmd_info *get_cmd_info(struct intel_gvt *gvt,
		u32 cmd, int ring_id)
{
	u32 opcode;

	opcode = get_opcode(cmd, ring_id);
	if (opcode == INVALID_OP)
		return NULL;

	return find_cmd_entry(gvt, opcode, ring_id);
}