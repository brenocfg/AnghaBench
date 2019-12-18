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
struct ks_wlan_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks_wlan_hw_tx (struct ks_wlan_private*,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps_confirm_wait_inc (struct ks_wlan_private*) ; 

__attribute__((used)) static inline void send_request_to_device(struct ks_wlan_private *priv,
					  void *data, size_t size)
{
	ps_confirm_wait_inc(priv);
	ks_wlan_hw_tx(priv, data, size, NULL, NULL);
}