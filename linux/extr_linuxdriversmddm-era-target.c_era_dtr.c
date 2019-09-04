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
struct dm_target {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  era_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void era_dtr(struct dm_target *ti)
{
	era_destroy(ti->private);
}