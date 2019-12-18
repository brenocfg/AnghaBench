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
typedef  int u32 ;
struct decode_info {int op_len; } ;

/* Variables and functions */
 size_t CMD_TYPE (int) ; 
 int INVALID_OP ; 
 struct decode_info*** ring_decode_info ; 

__attribute__((used)) static inline u32 get_opcode(u32 cmd, int ring_id)
{
	const struct decode_info *d_info;

	d_info = ring_decode_info[ring_id][CMD_TYPE(cmd)];
	if (d_info == NULL)
		return INVALID_OP;

	return cmd >> (32 - d_info->op_len);
}