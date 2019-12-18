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
typedef  scalar_t__ u32 ;
struct tegra_tcu {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ TCU_MBOX_NUM_BYTES (unsigned int) ; 
 int /*<<< orphan*/  mbox_flush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mbox_send_message (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void tegra_tcu_write_one(struct tegra_tcu *tcu, u32 value,
				unsigned int count)
{
	void *msg;

	value |= TCU_MBOX_NUM_BYTES(count);
	msg = (void *)(unsigned long)value;
	mbox_send_message(tcu->tx, msg);
	mbox_flush(tcu->tx, 1000);
}