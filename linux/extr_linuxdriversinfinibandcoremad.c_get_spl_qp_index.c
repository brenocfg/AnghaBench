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
#define  IB_QPT_GSI 129 
#define  IB_QPT_SMI 128 

__attribute__((used)) static int get_spl_qp_index(enum ib_qp_type qp_type)
{
	switch (qp_type)
	{
	case IB_QPT_SMI:
		return 0;
	case IB_QPT_GSI:
		return 1;
	default:
		return -1;
	}
}