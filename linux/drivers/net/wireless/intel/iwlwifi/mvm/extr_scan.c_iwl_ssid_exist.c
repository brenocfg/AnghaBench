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
typedef  scalar_t__ u8 ;
struct iwl_ssid_ie {scalar_t__ len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int PROBE_OPTION_MAX ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int iwl_ssid_exist(u8 *ssid, u8 ssid_len, struct iwl_ssid_ie *ssid_list)
{
	int i;

	for (i = 0; i < PROBE_OPTION_MAX; i++) {
		if (!ssid_list[i].len)
			break;
		if (ssid_list[i].len == ssid_len &&
		    !memcmp(ssid_list->ssid, ssid, ssid_len))
			return i;
	}
	return -1;
}