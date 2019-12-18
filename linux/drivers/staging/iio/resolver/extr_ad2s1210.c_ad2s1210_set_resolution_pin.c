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
struct ad2s1210_state {int resolution; int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 size_t AD2S1210_RES0 ; 
 size_t AD2S1210_RES1 ; 
 int /*<<< orphan*/ ** ad2s1210_res_pins ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ad2s1210_set_resolution_pin(struct ad2s1210_state *st)
{
	gpiod_set_value(st->gpios[AD2S1210_RES0],
			ad2s1210_res_pins[(st->resolution - 10) / 2][0]);
	gpiod_set_value(st->gpios[AD2S1210_RES1],
			ad2s1210_res_pins[(st->resolution - 10) / 2][1]);
}