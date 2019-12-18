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
struct TYPE_3__ {scalar_t__ stop; scalar_t__ last_failure_time; scalar_t__ failure; } ;
struct TYPE_4__ {int rsn_enabled; TYPE_1__ mic_failure; } ;
struct ks_wlan_private {TYPE_2__ wpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hostif_wpa_init(struct ks_wlan_private *priv)
{
	memset(&priv->wpa, 0, sizeof(priv->wpa));
	priv->wpa.rsn_enabled = false;
	priv->wpa.mic_failure.failure = 0;
	priv->wpa.mic_failure.last_failure_time = 0;
	priv->wpa.mic_failure.stop = 0;
}