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
typedef  enum ib_qp_create_flags { ____Placeholder_ib_qp_create_flags } ib_qp_create_flags ;

/* Variables and functions */
 int IB_QP_CREATE_RESERVED_START ; 

__attribute__((used)) static inline enum ib_qp_create_flags mlx5_ib_create_qp_sqpn_qp1(void)
{
	return IB_QP_CREATE_RESERVED_START;
}