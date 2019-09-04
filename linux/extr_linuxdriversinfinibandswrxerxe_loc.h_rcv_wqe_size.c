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
struct rxe_recv_wqe {int dummy; } ;
struct ib_sge {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int rcv_wqe_size(int max_sge)
{
	return sizeof(struct rxe_recv_wqe) +
		max_sge * sizeof(struct ib_sge);
}