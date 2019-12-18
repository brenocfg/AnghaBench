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
struct TYPE_2__ {int authType; } ;
struct airo_info {int last_auth; TYPE_1__ config; } ;

/* Variables and functions */
 int AUTH_ENCRYPT ; 
 int AUTH_OPEN ; 

__attribute__((used)) static inline void set_auth_type(struct airo_info *local, int auth_type)
{
	local->config.authType = auth_type;
	/* Cache the last auth type used (of AUTH_OPEN and AUTH_ENCRYPT).
	 * Used by airo_set_auth()
	 */
	if (auth_type == AUTH_OPEN || auth_type == AUTH_ENCRYPT)
		local->last_auth = auth_type;
}