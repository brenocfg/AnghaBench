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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_sq_wqe {int dummy; } ;
struct hinic_sq {int /*<<< orphan*/  wq; } ;
struct hinic_hw_wqe {struct hinic_sq_wqe sq_wqe; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct hinic_hw_wqe*) ; 
 struct hinic_hw_wqe* hinic_get_wqe (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

struct hinic_sq_wqe *hinic_sq_get_wqe(struct hinic_sq *sq,
				      unsigned int wqe_size, u16 *prod_idx)
{
	struct hinic_hw_wqe *hw_wqe = hinic_get_wqe(sq->wq, wqe_size,
						    prod_idx);

	if (IS_ERR(hw_wqe))
		return NULL;

	return &hw_wqe->sq_wqe;
}