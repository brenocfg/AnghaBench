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
struct b43_wldev {int dummy; } ;
struct b2056_inittabs_pts {int /*<<< orphan*/  rx_length; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx_length; int /*<<< orphan*/  tx; int /*<<< orphan*/  syn_length; int /*<<< orphan*/  syn; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2056_RX0 ; 
 int /*<<< orphan*/  B2056_RX1 ; 
 int /*<<< orphan*/  B2056_SYN ; 
 int /*<<< orphan*/  B2056_TX0 ; 
 int /*<<< orphan*/  B2056_TX1 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b2056_upload_inittab (struct b43_wldev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct b2056_inittabs_pts* b43_nphy_get_inittabs_rev3 (struct b43_wldev*) ; 

void b2056_upload_inittabs(struct b43_wldev *dev,
			   bool ghz5, bool ignore_uploadflag)
{
	const struct b2056_inittabs_pts *pts;

	pts = b43_nphy_get_inittabs_rev3(dev);
	if (!pts) {
		B43_WARN_ON(1);
		return;
	}

	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_SYN, pts->syn, pts->syn_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_TX0, pts->tx, pts->tx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_TX1, pts->tx, pts->tx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_RX0, pts->rx, pts->rx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_RX1, pts->rx, pts->rx_length);
}