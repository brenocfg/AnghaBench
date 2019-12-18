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
struct hinic_wq {int /*<<< orphan*/  delta; } ;
struct hinic_sq {struct hinic_wq* wq; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

int hinic_get_sq_free_wqebbs(struct hinic_sq *sq)
{
	struct hinic_wq *wq = sq->wq;

	return atomic_read(&wq->delta) - 1;
}