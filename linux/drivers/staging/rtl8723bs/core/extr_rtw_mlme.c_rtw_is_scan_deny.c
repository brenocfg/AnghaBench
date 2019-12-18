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
struct mlme_priv {int /*<<< orphan*/  set_scan_deny; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

inline bool rtw_is_scan_deny(struct adapter *adapter)
{
	struct mlme_priv *mlmepriv = &adapter->mlmepriv;
	return (atomic_read(&mlmepriv->set_scan_deny) != 0) ? true : false;
}