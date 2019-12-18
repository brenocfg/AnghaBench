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
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int qed_set_queue_coalesce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int qed_set_coalesce(struct qed_dev *cdev, u16 rx_coal, u16 tx_coal,
			    void *handle)
{
		return qed_set_queue_coalesce(rx_coal, tx_coal, handle);
}