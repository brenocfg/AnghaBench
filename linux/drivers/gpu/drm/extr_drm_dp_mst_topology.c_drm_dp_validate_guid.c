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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct drm_dp_mst_topology_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_jiffies_64 () ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool drm_dp_validate_guid(struct drm_dp_mst_topology_mgr *mgr,
				 u8 *guid)
{
	u64 salt;

	if (memchr_inv(guid, 0, 16))
		return true;

	salt = get_jiffies_64();

	memcpy(&guid[0], &salt, sizeof(u64));
	memcpy(&guid[8], &salt, sizeof(u64));

	return false;
}