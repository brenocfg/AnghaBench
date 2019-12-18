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
struct hfi1_opa_header {int /*<<< orphan*/  opah; int /*<<< orphan*/  ibh; int /*<<< orphan*/  hdr_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_16b_hdr_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __get_ib_hdr_len (int /*<<< orphan*/ *) ; 

u8 hfi1_trace_opa_hdr_len(struct hfi1_opa_header *opa_hdr)
{
	if (!opa_hdr->hdr_type)
		return __get_ib_hdr_len(&opa_hdr->ibh);
	else
		return __get_16b_hdr_len(&opa_hdr->opah);
}