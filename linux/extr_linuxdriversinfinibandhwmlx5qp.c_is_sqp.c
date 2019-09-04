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
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 scalar_t__ is_qp0 (int) ; 
 scalar_t__ is_qp1 (int) ; 

__attribute__((used)) static int is_sqp(enum ib_qp_type qp_type)
{
	return is_qp0(qp_type) || is_qp1(qp_type);
}