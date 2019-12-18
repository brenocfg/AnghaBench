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
struct hinic_sq {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_return_wqe (int /*<<< orphan*/ ,unsigned int) ; 

void hinic_sq_return_wqe(struct hinic_sq *sq, unsigned int wqe_size)
{
	hinic_return_wqe(sq->wq, wqe_size);
}