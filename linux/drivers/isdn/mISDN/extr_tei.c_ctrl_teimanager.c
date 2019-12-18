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
struct manager {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IMCLEAR_L2 129 
#define  IMHOLD_L1 128 
 int /*<<< orphan*/  OPTION_L1_HOLD ; 
 int /*<<< orphan*/  OPTION_L2_CLEANUP ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctrl_teimanager(struct manager *mgr, void *arg)
{
	/* currently we only have one option */
	unsigned int *val = (unsigned int *)arg;

	switch (val[0]) {
	case IMCLEAR_L2:
		if (val[1])
			test_and_set_bit(OPTION_L2_CLEANUP, &mgr->options);
		else
			test_and_clear_bit(OPTION_L2_CLEANUP, &mgr->options);
		break;
	case IMHOLD_L1:
		if (val[1])
			test_and_set_bit(OPTION_L1_HOLD, &mgr->options);
		else
			test_and_clear_bit(OPTION_L1_HOLD, &mgr->options);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}