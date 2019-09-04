#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cs_hsi_iface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct cs_hsi_iface* hi; } ;

/* Variables and functions */
 TYPE_1__ cs_char_data ; 
 int /*<<< orphan*/  cs_char_miscdev ; 
 int /*<<< orphan*/  cs_hsi_stop (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_hsi_client_remove(struct device *dev)
{
	struct cs_hsi_iface *hi;

	dev_dbg(dev, "hsi_client_remove\n");
	misc_deregister(&cs_char_miscdev);
	spin_lock_bh(&cs_char_data.lock);
	hi = cs_char_data.hi;
	cs_char_data.hi = NULL;
	spin_unlock_bh(&cs_char_data.lock);
	if (hi)
		cs_hsi_stop(hi);

	return 0;
}