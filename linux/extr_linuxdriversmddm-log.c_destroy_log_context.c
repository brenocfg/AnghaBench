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
struct log_c {int /*<<< orphan*/  recovering_bits; int /*<<< orphan*/  sync_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct log_c*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_log_context(struct log_c *lc)
{
	vfree(lc->sync_bits);
	vfree(lc->recovering_bits);
	kfree(lc);
}