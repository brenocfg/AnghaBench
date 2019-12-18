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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPLIT_TYPE_NONE ; 
 int qed_grc_dump_addr_range (struct qed_hwfn*,struct qed_ptt*,int*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_grc_dump_mem_hdr (struct qed_hwfn*,int*,int,char const*,int,int,int,int,char const*,int,char) ; 

__attribute__((used)) static u32 qed_grc_dump_mem(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt,
			    u32 *dump_buf,
			    bool dump,
			    const char *name,
			    u32 addr,
			    u32 len,
			    bool wide_bus,
			    u32 bit_width,
			    bool packed,
			    const char *mem_group,
			    bool is_storm, char storm_letter)
{
	u32 offset = 0;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       name,
				       addr,
				       len,
				       bit_width,
				       packed,
				       mem_group, is_storm, storm_letter);
	offset += qed_grc_dump_addr_range(p_hwfn,
					  p_ptt,
					  dump_buf + offset,
					  dump, addr, len, wide_bus,
					  SPLIT_TYPE_NONE, 0);

	return offset;
}