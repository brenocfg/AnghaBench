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
typedef  int /*<<< orphan*/  u32 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_radio_id (struct brcms_phy*) ; 

__attribute__((used)) static u32 wlc_phy_get_radio_ver(struct brcms_phy *pi)
{
	u32 ver;

	ver = read_radio_id(pi);

	return ver;
}