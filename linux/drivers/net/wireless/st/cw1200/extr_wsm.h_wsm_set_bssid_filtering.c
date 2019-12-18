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
struct wsm_set_bssid_filtering {int filter; } ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  WSM_MIB_ID_DISABLE_BSSID_FILTER ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,struct wsm_set_bssid_filtering*,int) ; 

__attribute__((used)) static inline int wsm_set_bssid_filtering(struct cw1200_common *priv,
					  bool enabled)
{
	struct wsm_set_bssid_filtering arg = {
		.filter = !enabled,
	};
	return wsm_write_mib(priv, WSM_MIB_ID_DISABLE_BSSID_FILTER,
			&arg, sizeof(arg));
}