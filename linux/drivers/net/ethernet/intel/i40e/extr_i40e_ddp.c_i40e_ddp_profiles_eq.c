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
struct i40e_profile_info {scalar_t__ track_id; int /*<<< orphan*/  name; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int I40E_DDP_NAME_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool i40e_ddp_profiles_eq(struct i40e_profile_info *a,
				 struct i40e_profile_info *b)
{
	return a->track_id == b->track_id &&
		!memcmp(&a->version, &b->version, sizeof(a->version)) &&
		!memcmp(&a->name, &b->name, I40E_DDP_NAME_SIZE);
}