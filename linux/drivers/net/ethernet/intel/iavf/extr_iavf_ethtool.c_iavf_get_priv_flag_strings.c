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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {char* flag_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 unsigned int IAVF_PRIV_FLAGS_STR_LEN ; 
 TYPE_1__* iavf_gstrings_priv_flags ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void iavf_get_priv_flag_strings(struct net_device *netdev, u8 *data)
{
	unsigned int i;

	for (i = 0; i < IAVF_PRIV_FLAGS_STR_LEN; i++) {
		snprintf(data, ETH_GSTRING_LEN, "%s",
			 iavf_gstrings_priv_flags[i].flag_string);
		data += ETH_GSTRING_LEN;
	}
}