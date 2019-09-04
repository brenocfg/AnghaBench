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
struct drxk_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  mpegts_stop (struct drxk_state*) ; 

__attribute__((used)) static int shut_down(struct drxk_state *state)
{
	dprintk(1, "\n");

	mpegts_stop(state);
	return 0;
}