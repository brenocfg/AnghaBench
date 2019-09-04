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
struct intel_fbdev {scalar_t__ cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_synchronize_cookie (scalar_t__) ; 

__attribute__((used)) static void intel_fbdev_sync(struct intel_fbdev *ifbdev)
{
	if (!ifbdev->cookie)
		return;

	/* Only serialises with all preceding async calls, hence +1 */
	async_synchronize_cookie(ifbdev->cookie + 1);
	ifbdev->cookie = 0;
}