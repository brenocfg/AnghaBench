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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct hifn_device {int dummy; } ;
struct hifn_base_command {void* session_num; void* total_dest_count; void* total_source_count; void* masks; } ;

/* Variables and functions */
 unsigned int HIFN_BASE_CMD_DSTLEN_M ; 
 unsigned int HIFN_BASE_CMD_DSTLEN_S ; 
 unsigned int HIFN_BASE_CMD_LENMASK_LO ; 
 unsigned int HIFN_BASE_CMD_SRCLEN_M ; 
 unsigned int HIFN_BASE_CMD_SRCLEN_S ; 
 void* __cpu_to_le16 (unsigned int) ; 

__attribute__((used)) static int hifn_setup_base_command(struct hifn_device *dev, u8 *buf,
		unsigned dlen, unsigned slen, u16 mask, u8 snum)
{
	struct hifn_base_command *base_cmd;
	u8 *buf_pos = buf;

	base_cmd = (struct hifn_base_command *)buf_pos;
	base_cmd->masks = __cpu_to_le16(mask);
	base_cmd->total_source_count =
		__cpu_to_le16(slen & HIFN_BASE_CMD_LENMASK_LO);
	base_cmd->total_dest_count =
		__cpu_to_le16(dlen & HIFN_BASE_CMD_LENMASK_LO);

	dlen >>= 16;
	slen >>= 16;
	base_cmd->session_num = __cpu_to_le16(snum |
	    ((slen << HIFN_BASE_CMD_SRCLEN_S) & HIFN_BASE_CMD_SRCLEN_M) |
	    ((dlen << HIFN_BASE_CMD_DSTLEN_S) & HIFN_BASE_CMD_DSTLEN_M));

	return sizeof(struct hifn_base_command);
}