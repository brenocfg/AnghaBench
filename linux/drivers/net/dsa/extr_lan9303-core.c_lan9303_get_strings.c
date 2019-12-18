#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u32 ;
struct dsa_switch {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 TYPE_1__* lan9303_mib ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void lan9303_get_strings(struct dsa_switch *ds, int port,
				u32 stringset, uint8_t *data)
{
	unsigned int u;

	if (stringset != ETH_SS_STATS)
		return;

	for (u = 0; u < ARRAY_SIZE(lan9303_mib); u++) {
		strncpy(data + u * ETH_GSTRING_LEN, lan9303_mib[u].name,
			ETH_GSTRING_LEN);
	}
}