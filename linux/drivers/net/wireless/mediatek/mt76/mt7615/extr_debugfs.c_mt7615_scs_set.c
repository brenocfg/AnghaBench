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
typedef  int /*<<< orphan*/  u64 ;
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7615_mac_set_scs (struct mt7615_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7615_scs_set(void *data, u64 val)
{
	struct mt7615_dev *dev = data;

	mt7615_mac_set_scs(dev, val);

	return 0;
}