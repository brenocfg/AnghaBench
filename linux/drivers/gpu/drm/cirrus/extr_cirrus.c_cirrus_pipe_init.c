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
struct cirrus_device {int /*<<< orphan*/  conn; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cirrus_formats ; 
 int /*<<< orphan*/  cirrus_modifiers ; 
 int /*<<< orphan*/  cirrus_pipe_funcs ; 
 int drm_simple_display_pipe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cirrus_pipe_init(struct cirrus_device *cirrus)
{
	return drm_simple_display_pipe_init(&cirrus->dev,
					    &cirrus->pipe,
					    &cirrus_pipe_funcs,
					    cirrus_formats,
					    ARRAY_SIZE(cirrus_formats),
					    cirrus_modifiers,
					    &cirrus->conn);
}