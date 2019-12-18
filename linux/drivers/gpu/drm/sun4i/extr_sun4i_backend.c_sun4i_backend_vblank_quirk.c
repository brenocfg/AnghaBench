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
struct sunxi_engine {int dummy; } ;
struct sun4i_frontend {int dummy; } ;
struct sun4i_backend {int frontend_teardown; int /*<<< orphan*/  frontend_lock; struct sun4i_frontend* frontend; } ;

/* Variables and functions */
 struct sun4i_backend* engine_to_sun4i_backend (struct sunxi_engine*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4i_frontend_exit (struct sun4i_frontend*) ; 

__attribute__((used)) static void sun4i_backend_vblank_quirk(struct sunxi_engine *engine)
{
	struct sun4i_backend *backend = engine_to_sun4i_backend(engine);
	struct sun4i_frontend *frontend = backend->frontend;

	if (!frontend)
		return;

	/*
	 * In a teardown scenario with the frontend involved, we have
	 * to keep the frontend enabled until the next vblank, and
	 * only then disable it.
	 *
	 * This is due to the fact that the backend will not take into
	 * account the new configuration (with the plane that used to
	 * be fed by the frontend now disabled) until we write to the
	 * commit bit and the hardware fetches the new configuration
	 * during the next vblank.
	 *
	 * So we keep the frontend around in order to prevent any
	 * visual artifacts.
	 */
	spin_lock(&backend->frontend_lock);
	if (backend->frontend_teardown) {
		sun4i_frontend_exit(frontend);
		backend->frontend_teardown = false;
	}
	spin_unlock(&backend->frontend_lock);
}