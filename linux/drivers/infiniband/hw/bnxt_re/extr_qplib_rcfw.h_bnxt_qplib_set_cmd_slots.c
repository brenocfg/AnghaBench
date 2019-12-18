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
struct cmdq_base {int cmd_size; } ;

/* Variables and functions */
 int BNXT_QPLIB_CMDQE_UNITS ; 

__attribute__((used)) static inline void bnxt_qplib_set_cmd_slots(struct cmdq_base *req)
{
	req->cmd_size = (req->cmd_size + BNXT_QPLIB_CMDQE_UNITS - 1) /
			 BNXT_QPLIB_CMDQE_UNITS;
}