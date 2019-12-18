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
struct mux {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  mux_control_deselect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iio_mux_deselect(struct mux *mux)
{
	mux_control_deselect(mux->control);
}