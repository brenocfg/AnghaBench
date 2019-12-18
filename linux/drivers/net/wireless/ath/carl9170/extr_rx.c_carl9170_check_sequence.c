#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cmd_bufs; } ;
struct ar9170 {int cmd_seq; TYPE_2__ fw; TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_RR_LOST_RSP ; 
 int EIO ; 
 int /*<<< orphan*/  carl9170_restart (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int carl9170_check_sequence(struct ar9170 *ar, unsigned int seq)
{
	if (ar->cmd_seq < -1)
		return 0;

	/*
	 * Initialize Counter
	 */
	if (ar->cmd_seq < 0)
		ar->cmd_seq = seq;

	/*
	 * The sequence is strictly monotonic increasing and it never skips!
	 *
	 * Therefore we can safely assume that whenever we received an
	 * unexpected sequence we have lost some valuable data.
	 */
	if (seq != ar->cmd_seq) {
		int count;

		count = (seq - ar->cmd_seq) % ar->fw.cmd_bufs;

		wiphy_err(ar->hw->wiphy, "lost %d command responses/traps! "
			  "w:%d g:%d\n", count, ar->cmd_seq, seq);

		carl9170_restart(ar, CARL9170_RR_LOST_RSP);
		return -EIO;
	}

	ar->cmd_seq = (ar->cmd_seq + 1) % ar->fw.cmd_bufs;
	return 0;
}