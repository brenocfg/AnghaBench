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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  defx ; 
 int /*<<< orphan*/  defy ; 
 int drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 int /*<<< orphan*/  drm_set_preferred_mode (struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bochs_connector_get_modes(struct drm_connector *connector)
{
	int count;

	count = drm_add_modes_noedid(connector, 8192, 8192);
	drm_set_preferred_mode(connector, defx, defy);
	return count;
}