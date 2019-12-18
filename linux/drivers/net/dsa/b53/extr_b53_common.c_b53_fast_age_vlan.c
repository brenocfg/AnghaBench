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
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_FAST_AGE_VID_CTRL ; 
 int /*<<< orphan*/  FAST_AGE_VLAN ; 
 int b53_flush_arl (struct b53_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b53_fast_age_vlan(struct b53_device *dev, u16 vid)
{
	b53_write16(dev, B53_CTRL_PAGE, B53_FAST_AGE_VID_CTRL, vid);

	return b53_flush_arl(dev, FAST_AGE_VLAN);
}