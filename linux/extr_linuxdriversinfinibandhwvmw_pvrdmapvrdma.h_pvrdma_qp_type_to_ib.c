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
typedef  enum pvrdma_qp_type { ____Placeholder_pvrdma_qp_type } pvrdma_qp_type ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */

__attribute__((used)) static inline enum ib_qp_type pvrdma_qp_type_to_ib(enum pvrdma_qp_type type)
{
	return (enum ib_qp_type)type;
}