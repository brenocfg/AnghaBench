#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * MacAddress; } ;
struct TYPE_4__ {TYPE_1__ network; } ;
struct mlme_priv {TYPE_2__ cur_network; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *get_bssid(struct mlme_priv *pmlmepriv)
{
	return pmlmepriv->cur_network.network.MacAddress;
}