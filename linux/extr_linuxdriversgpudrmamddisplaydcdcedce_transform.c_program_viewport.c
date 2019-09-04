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
struct rect {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct dce_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  VIEWPORT_SIZE ; 
 int /*<<< orphan*/  VIEWPORT_START ; 
 int /*<<< orphan*/  VIEWPORT_WIDTH ; 
 int /*<<< orphan*/  VIEWPORT_X_START ; 
 int /*<<< orphan*/  VIEWPORT_Y_START ; 

__attribute__((used)) static void program_viewport(
	struct dce_transform *xfm_dce,
	const struct rect *view_port)
{
	REG_SET_2(VIEWPORT_START, 0,
			VIEWPORT_X_START, view_port->x,
			VIEWPORT_Y_START, view_port->y);

	REG_SET_2(VIEWPORT_SIZE, 0,
			VIEWPORT_HEIGHT, view_port->height,
			VIEWPORT_WIDTH, view_port->width);

	/* TODO: add stereo support */
}