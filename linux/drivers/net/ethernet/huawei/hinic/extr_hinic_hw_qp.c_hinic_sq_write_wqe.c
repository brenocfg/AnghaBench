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
struct sk_buff {int dummy; } ;
struct hinic_sq_wqe {int dummy; } ;
struct hinic_sq {int /*<<< orphan*/  wq; struct sk_buff** saved_skb; } ;
struct hinic_hw_wqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_cpu_to_be32 (struct hinic_sq_wqe*,unsigned int) ; 
 int /*<<< orphan*/  hinic_write_wqe (int /*<<< orphan*/ ,struct hinic_hw_wqe*,unsigned int) ; 

void hinic_sq_write_wqe(struct hinic_sq *sq, u16 prod_idx,
			struct hinic_sq_wqe *sq_wqe,
			struct sk_buff *skb, unsigned int wqe_size)
{
	struct hinic_hw_wqe *hw_wqe = (struct hinic_hw_wqe *)sq_wqe;

	sq->saved_skb[prod_idx] = skb;

	/* The data in the HW should be in Big Endian Format */
	hinic_cpu_to_be32(sq_wqe, wqe_size);

	hinic_write_wqe(sq->wq, hw_wqe, wqe_size);
}