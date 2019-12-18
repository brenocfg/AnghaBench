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

/* Variables and functions */
 int /*<<< orphan*/  B43_GTAB_ORIGTR ; 
 int /*<<< orphan*/  b43_gtab_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_wa_tr_ltov(struct b43_wldev *dev) /* TR Lookup Table Original Values */
{
	b43_gtab_write(dev, B43_GTAB_ORIGTR, 0, 0x7654);
}