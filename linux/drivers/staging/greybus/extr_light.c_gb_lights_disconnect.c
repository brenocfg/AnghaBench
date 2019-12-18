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
struct gb_lights {int /*<<< orphan*/  connection; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_lights_release (struct gb_lights*) ; 
 int /*<<< orphan*/  gb_pm_runtime_get_noresume (struct gb_bundle*) ; 
 scalar_t__ gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 struct gb_lights* greybus_get_drvdata (struct gb_bundle*) ; 

__attribute__((used)) static void gb_lights_disconnect(struct gb_bundle *bundle)
{
	struct gb_lights *glights = greybus_get_drvdata(bundle);

	if (gb_pm_runtime_get_sync(bundle))
		gb_pm_runtime_get_noresume(bundle);

	gb_connection_disable(glights->connection);
	gb_connection_destroy(glights->connection);

	gb_lights_release(glights);
}