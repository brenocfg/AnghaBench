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
struct qed_iscsi_ops {int dummy; } ;

/* Variables and functions */
 struct qed_iscsi_ops const qed_iscsi_ops_pass ; 

const struct qed_iscsi_ops *qed_get_iscsi_ops(void)
{
	return &qed_iscsi_ops_pass;
}