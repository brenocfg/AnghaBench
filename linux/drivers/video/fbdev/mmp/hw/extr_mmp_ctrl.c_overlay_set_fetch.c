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
struct mmp_overlay {int dmafetch_id; } ;

/* Variables and functions */

__attribute__((used)) static void overlay_set_fetch(struct mmp_overlay *overlay, int fetch_id)
{
	overlay->dmafetch_id = fetch_id;
}