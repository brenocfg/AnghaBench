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
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct eth_slow_path_rx_cqe {int /*<<< orphan*/  echo; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int qed_spq_completion (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_cqe_completion(struct qed_hwfn *p_hwfn,
			      struct eth_slow_path_rx_cqe *cqe,
			      enum protocol_type protocol)
{
	if (IS_VF(p_hwfn->cdev))
		return 0;

	/* @@@tmp - it's possible we'll eventually want to handle some
	 * actual commands that can arrive here, but for now this is only
	 * used to complete the ramrod using the echo value on the cqe
	 */
	return qed_spq_completion(p_hwfn, cqe->echo, 0, NULL);
}