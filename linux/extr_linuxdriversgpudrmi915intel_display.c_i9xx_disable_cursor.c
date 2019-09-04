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
struct intel_plane {int dummy; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i9xx_update_cursor (struct intel_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i9xx_disable_cursor(struct intel_plane *plane,
				struct intel_crtc *crtc)
{
	i9xx_update_cursor(plane, NULL, NULL);
}