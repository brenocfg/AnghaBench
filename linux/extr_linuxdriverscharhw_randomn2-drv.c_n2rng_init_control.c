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
struct n2rng {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  n2rng_control_swstate_init (struct n2rng*) ; 
 int n2rng_grab_diag_control (struct n2rng*) ; 

__attribute__((used)) static int n2rng_init_control(struct n2rng *np)
{
	int err = n2rng_grab_diag_control(np);

	/* Not in the control domain, that's OK we are only a consumer
	 * of the RNG data, we don't setup and program it.
	 */
	if (err == -EPERM)
		return 0;
	if (err)
		return err;

	n2rng_control_swstate_init(np);

	return 0;
}