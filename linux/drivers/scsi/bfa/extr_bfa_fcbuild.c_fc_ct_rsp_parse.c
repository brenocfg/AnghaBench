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
typedef  int /*<<< orphan*/  u16 ;
struct ct_hdr_s {scalar_t__ reason_code; int /*<<< orphan*/  cmd_rsp_code; } ;

/* Variables and functions */
 scalar_t__ CT_RSN_LOGICAL_BUSY ; 
 scalar_t__ CT_RSP_ACCEPT ; 
 int /*<<< orphan*/  FC_PARSE_BUSY ; 
 int /*<<< orphan*/  FC_PARSE_FAILURE ; 
 int /*<<< orphan*/  FC_PARSE_OK ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 

u16
fc_ct_rsp_parse(struct ct_hdr_s *cthdr)
{
	if (be16_to_cpu(cthdr->cmd_rsp_code) != CT_RSP_ACCEPT) {
		if (cthdr->reason_code == CT_RSN_LOGICAL_BUSY)
			return FC_PARSE_BUSY;
		else
			return FC_PARSE_FAILURE;
	}

	return FC_PARSE_OK;
}