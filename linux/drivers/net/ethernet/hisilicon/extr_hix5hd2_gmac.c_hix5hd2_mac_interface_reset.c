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
struct hix5hd2_priv {int /*<<< orphan*/  mac_ifc_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hix5hd2_mac_interface_reset(struct hix5hd2_priv *priv)
{
	if (!priv->mac_ifc_rst)
		return;

	reset_control_assert(priv->mac_ifc_rst);
	reset_control_deassert(priv->mac_ifc_rst);
}