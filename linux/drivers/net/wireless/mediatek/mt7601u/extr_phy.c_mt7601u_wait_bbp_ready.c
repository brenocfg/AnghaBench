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
typedef  int /*<<< orphan*/  u8 ;
struct mt7601u_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT_BBP_REG_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt7601u_bbp_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

int mt7601u_wait_bbp_ready(struct mt7601u_dev *dev)
{
	int i = 20;
	u8 val;

	do {
		val = mt7601u_bbp_rr(dev, MT_BBP_REG_VERSION);
		if (val && ~val)
			break;
	} while (--i);

	if (!i) {
		dev_err(dev->dev, "Error: BBP is not ready\n");
		return -EIO;
	}

	return 0;
}