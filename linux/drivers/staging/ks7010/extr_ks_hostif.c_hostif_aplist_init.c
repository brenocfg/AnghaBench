#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct local_ap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ap; int /*<<< orphan*/  size; } ;
struct ks_wlan_private {TYPE_1__ aplist; } ;

/* Variables and functions */
 int LOCAL_APLIST_MAX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void hostif_aplist_init(struct ks_wlan_private *priv)
{
	size_t size = LOCAL_APLIST_MAX * sizeof(struct local_ap);

	priv->aplist.size = 0;
	memset(&priv->aplist.ap[0], 0, size);
}