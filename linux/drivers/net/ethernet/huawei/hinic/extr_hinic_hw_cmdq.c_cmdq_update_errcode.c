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
typedef  size_t u16 ;
struct hinic_cmdq {int** errcode; } ;

/* Variables and functions */

__attribute__((used)) static void cmdq_update_errcode(struct hinic_cmdq *cmdq, u16 prod_idx,
				int errcode)
{
	if (cmdq->errcode[prod_idx])
		*cmdq->errcode[prod_idx] = errcode;
}