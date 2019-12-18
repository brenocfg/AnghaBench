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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ct_hdr_s {int /*<<< orphan*/  cmd_rsp_code; int /*<<< orphan*/  gs_sub_type; int /*<<< orphan*/  gs_type; int /*<<< orphan*/  rev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_GS3_REVISION ; 
 int /*<<< orphan*/  CT_GSTYPE_MGMTSERVICE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ct_hdr_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fc_gs_ms_cthdr_build(struct ct_hdr_s *cthdr, u32 s_id, u16 cmd_code,
					 u8 sub_type)
{
	memset(cthdr, 0, sizeof(struct ct_hdr_s));
	cthdr->rev_id = CT_GS3_REVISION;
	cthdr->gs_type = CT_GSTYPE_MGMTSERVICE;
	cthdr->gs_sub_type = sub_type;
	cthdr->cmd_rsp_code = cpu_to_be16(cmd_code);
}