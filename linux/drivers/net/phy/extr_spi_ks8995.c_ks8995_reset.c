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
struct ks8995_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8995_RESET_DELAY ; 
 int ks8995_start (struct ks8995_switch*) ; 
 int ks8995_stop (struct ks8995_switch*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks8995_reset(struct ks8995_switch *ks)
{
	int err;

	err = ks8995_stop(ks);
	if (err)
		return err;

	udelay(KS8995_RESET_DELAY);

	return ks8995_start(ks);
}