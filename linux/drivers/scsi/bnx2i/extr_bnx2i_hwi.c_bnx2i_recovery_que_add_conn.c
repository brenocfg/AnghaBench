#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnx2i_hba {int dummy; } ;
struct bnx2i_conn {TYPE_1__* cls_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  iscsi_conn_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_recovery_que_add_conn(struct bnx2i_hba *hba,
					struct bnx2i_conn *bnx2i_conn)
{
	iscsi_conn_failure(bnx2i_conn->cls_conn->dd_data,
			   ISCSI_ERR_CONN_FAILED);
}