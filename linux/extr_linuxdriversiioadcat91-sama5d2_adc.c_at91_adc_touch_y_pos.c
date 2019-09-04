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
typedef  int /*<<< orphan*/  u16 ;
struct at91_adc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_YPOSR ; 
 int /*<<< orphan*/  at91_adc_touch_pos (struct at91_adc_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 at91_adc_touch_y_pos(struct at91_adc_state *st)
{
	return at91_adc_touch_pos(st, AT91_SAMA5D2_YPOSR);
}