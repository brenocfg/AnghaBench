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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DATA ; 
 int /*<<< orphan*/  RT_IDX ; 
 int RT_IDX_IDX_SHIFT ; 
 int /*<<< orphan*/  RT_IDX_MR ; 
 int /*<<< orphan*/  RT_IDX_MW ; 
 int RT_IDX_RS ; 
 int RT_IDX_TYPE_NICQ ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

int ql_get_routing_reg(struct ql_adapter *qdev, u32 index, u32 *value)
{
	int status = 0;

	status = ql_wait_reg_rdy(qdev, RT_IDX, RT_IDX_MW, 0);
	if (status)
		goto exit;

	ql_write32(qdev, RT_IDX,
		   RT_IDX_TYPE_NICQ | RT_IDX_RS | (index << RT_IDX_IDX_SHIFT));
	status = ql_wait_reg_rdy(qdev, RT_IDX, RT_IDX_MR, 0);
	if (status)
		goto exit;
	*value = ql_read32(qdev, RT_DATA);
exit:
	return status;
}