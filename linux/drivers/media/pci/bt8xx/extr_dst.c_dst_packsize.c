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
union dst_gpio_packet {int psize; } ;
struct dst_state {int /*<<< orphan*/  bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_IG_TS ; 
 int /*<<< orphan*/  bt878_device_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union dst_gpio_packet*) ; 

__attribute__((used)) static void dst_packsize(struct dst_state *state, int psize)
{
	union dst_gpio_packet bits;

	bits.psize = psize;
	bt878_device_control(state->bt, DST_IG_TS, &bits);
}