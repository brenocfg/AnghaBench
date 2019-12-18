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
struct hinic_sq {struct sk_buff** saved_skb; int /*<<< orphan*/  wq; } ;
struct hinic_hw_wqe {struct hinic_sq_wqe sq_wqe; } ;

/* Variables and functions */
 struct hinic_hw_wqe* hinic_read_wqe (int /*<<< orphan*/ ,unsigned int,size_t*) ; 

struct hinic_sq_wqe *hinic_sq_read_wqe(struct hinic_sq *sq,
				       struct sk_buff **skb,
				       unsigned int wqe_size, u16 *cons_idx)
{
	struct hinic_hw_wqe *hw_wqe;

	hw_wqe = hinic_read_wqe(sq->wq, wqe_size, cons_idx);
	*skb = sq->saved_skb[*cons_idx];

	return &hw_wqe->sq_wqe;
}