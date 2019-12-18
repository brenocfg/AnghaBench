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
struct hnae_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_get_mac_cb (struct hnae_handle*) ; 
 int hns_mac_set_autoneg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_ae_set_autoneg(struct hnae_handle *handle, u8 enable)
{
	assert(handle);

	return hns_mac_set_autoneg(hns_get_mac_cb(handle), enable);
}