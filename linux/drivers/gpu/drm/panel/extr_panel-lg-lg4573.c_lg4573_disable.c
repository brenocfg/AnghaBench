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
struct lg4573 {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int lg4573_display_off (struct lg4573*) ; 
 struct lg4573* panel_to_lg4573 (struct drm_panel*) ; 

__attribute__((used)) static int lg4573_disable(struct drm_panel *panel)
{
	struct lg4573 *ctx = panel_to_lg4573(panel);

	return lg4573_display_off(ctx);
}