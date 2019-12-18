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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_RMT_INDICATION (struct s_smc*,int) ; 
 int /*<<< orphan*/  LED_Y_OFF ; 
 int /*<<< orphan*/  LED_Y_ON ; 
 int /*<<< orphan*/  led_indication (struct s_smc*,int /*<<< orphan*/ ) ; 

void rmt_indication(struct s_smc *smc, int i)
{
	/* Call a driver special function if defined */
	DRV_RMT_INDICATION(smc,i) ;

        led_indication(smc, i ? LED_Y_OFF : LED_Y_ON) ;
}