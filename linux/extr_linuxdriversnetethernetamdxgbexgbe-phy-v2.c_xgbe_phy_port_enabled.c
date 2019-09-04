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
struct xgbe_prv_data {int /*<<< orphan*/  pp0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_TYPE ; 
 int /*<<< orphan*/  PORT_SPEEDS ; 
 int /*<<< orphan*/  XP_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_PROP_0 ; 

__attribute__((used)) static bool xgbe_phy_port_enabled(struct xgbe_prv_data *pdata)
{
	if (!XP_GET_BITS(pdata->pp0, XP_PROP_0, PORT_SPEEDS))
		return false;
	if (!XP_GET_BITS(pdata->pp0, XP_PROP_0, CONN_TYPE))
		return false;

	return true;
}