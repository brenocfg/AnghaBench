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
struct wil6210_priv {int /*<<< orphan*/  mutex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct wil6210_priv* ndev_to_wil (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 

__attribute__((used)) static int wil_ethtoolops_begin(struct net_device *ndev)
{
	struct wil6210_priv *wil = ndev_to_wil(ndev);

	mutex_lock(&wil->mutex);

	wil_dbg_misc(wil, "ethtoolops_begin\n");

	return 0;
}