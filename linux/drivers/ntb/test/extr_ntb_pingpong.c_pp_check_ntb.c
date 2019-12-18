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
typedef  int u64 ;
struct ntb_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK_ULL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ntb_db_is_unsafe (struct ntb_dev*) ; 
 int ntb_db_valid_mask (struct ntb_dev*) ; 
 int ntb_msg_count (struct ntb_dev*) ; 
 int /*<<< orphan*/  ntb_peer_port_count (struct ntb_dev*) ; 
 int ntb_spad_count (struct ntb_dev*) ; 
 scalar_t__ ntb_spad_is_unsafe (struct ntb_dev*) ; 
 int /*<<< orphan*/  unsafe ; 

__attribute__((used)) static int pp_check_ntb(struct ntb_dev *ntb)
{
	u64 pmask;

	if (ntb_db_is_unsafe(ntb)) {
		dev_dbg(&ntb->dev, "Doorbell is unsafe\n");
		if (!unsafe)
			return -EINVAL;
	}

	if (ntb_spad_is_unsafe(ntb)) {
		dev_dbg(&ntb->dev, "Scratchpad is unsafe\n");
		if (!unsafe)
			return -EINVAL;
	}

	pmask = GENMASK_ULL(ntb_peer_port_count(ntb), 0);
	if ((ntb_db_valid_mask(ntb) & pmask) != pmask) {
		dev_err(&ntb->dev, "Unsupported DB configuration\n");
		return -EINVAL;
	}

	if (ntb_spad_count(ntb) < 1 && ntb_msg_count(ntb) < 1) {
		dev_err(&ntb->dev, "Scratchpads and messages unsupported\n");
		return -EINVAL;
	} else if (ntb_spad_count(ntb) < 1) {
		dev_dbg(&ntb->dev, "Scratchpads unsupported\n");
	} else if (ntb_msg_count(ntb) < 1) {
		dev_dbg(&ntb->dev, "Messages unsupported\n");
	}

	return 0;
}