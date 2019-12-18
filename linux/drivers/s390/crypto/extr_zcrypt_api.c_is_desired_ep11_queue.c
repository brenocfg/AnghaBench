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
struct ep11_target_dev {int /*<<< orphan*/  dom_id; int /*<<< orphan*/  ap_id; } ;

/* Variables and functions */
 unsigned int AP_MKQID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_desired_ep11_queue(unsigned int dev_qid,
				  unsigned short target_num,
				  struct ep11_target_dev *targets)
{
	while (target_num-- > 0) {
		if (AP_MKQID(targets->ap_id, targets->dom_id) == dev_qid)
			return true;
		targets++;
	}
	return false;
}