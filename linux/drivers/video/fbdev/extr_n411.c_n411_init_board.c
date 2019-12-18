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
struct hecubafb_par {int /*<<< orphan*/  (* send_data ) (struct hecubafb_par*,int) ;int /*<<< orphan*/  (* send_command ) (struct hecubafb_par*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APOLLO_ERASE_DISPLAY ; 
 int /*<<< orphan*/  APOLLO_INIT_DISPLAY ; 
 int n411_init_control (struct hecubafb_par*) ; 
 int /*<<< orphan*/  nosplash ; 
 int splashval ; 
 int /*<<< orphan*/  stub1 (struct hecubafb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hecubafb_par*,int) ; 
 int /*<<< orphan*/  stub3 (struct hecubafb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct hecubafb_par*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int n411_init_board(struct hecubafb_par *par)
{
	int retval;

	retval = n411_init_control(par);
	if (retval)
		return retval;

	par->send_command(par, APOLLO_INIT_DISPLAY);
	par->send_data(par, 0x81);

	/* have to wait while display resets */
	udelay(1000);

	/* if we were told to splash the screen, we just clear it */
	if (!nosplash) {
		par->send_command(par, APOLLO_ERASE_DISPLAY);
		par->send_data(par, splashval);
	}

	return 0;
}