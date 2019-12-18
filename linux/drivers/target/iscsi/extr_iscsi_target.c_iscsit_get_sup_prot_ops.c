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
struct iscsi_conn {int dummy; } ;
typedef  enum target_prot_op { ____Placeholder_target_prot_op } target_prot_op ;

/* Variables and functions */
 int TARGET_PROT_NORMAL ; 

__attribute__((used)) static enum target_prot_op iscsit_get_sup_prot_ops(struct iscsi_conn *conn)
{
	return TARGET_PROT_NORMAL;
}