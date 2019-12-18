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
struct platform_device {int dummy; } ;
struct mdio_mux_multiplexer_state {int /*<<< orphan*/  muxc; scalar_t__ do_deselect; int /*<<< orphan*/  mux_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdio_mux_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mux_control_deselect (int /*<<< orphan*/ ) ; 
 struct mdio_mux_multiplexer_state* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mdio_mux_multiplexer_remove(struct platform_device *pdev)
{
	struct mdio_mux_multiplexer_state *s = platform_get_drvdata(pdev);

	mdio_mux_uninit(s->mux_handle);

	if (s->do_deselect)
		mux_control_deselect(s->muxc);

	return 0;
}