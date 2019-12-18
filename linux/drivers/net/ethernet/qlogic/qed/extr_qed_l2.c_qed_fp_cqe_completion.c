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
typedef  size_t u8 ;
struct qed_dev {size_t num_hwfns; int /*<<< orphan*/ * hwfns; } ;
struct eth_slow_path_rx_cqe {int dummy; } ;

/* Variables and functions */
 int qed_eth_cqe_completion (int /*<<< orphan*/ *,struct eth_slow_path_rx_cqe*) ; 

__attribute__((used)) static int qed_fp_cqe_completion(struct qed_dev *dev,
				 u8 rss_id, struct eth_slow_path_rx_cqe *cqe)
{
	return qed_eth_cqe_completion(&dev->hwfns[rss_id % dev->num_hwfns],
				      cqe);
}