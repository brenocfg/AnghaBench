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
typedef  int u16 ;

/* Variables and functions */
#define  AD_ACTOR_CHURN_TIMER 132 
 int AD_AGGREGATE_WAIT_TIME ; 
 int AD_CHURN_DETECTION_TIME ; 
#define  AD_CURRENT_WHILE_TIMER 131 
 int AD_LONG_TIMEOUT_TIME ; 
#define  AD_PARTNER_CHURN_TIMER 130 
#define  AD_PERIODIC_TIMER 129 
 int AD_SHORT_TIMEOUT_TIME ; 
#define  AD_WAIT_WHILE_TIMER 128 
 int ad_ticks_per_sec ; 

__attribute__((used)) static u16 __ad_timer_to_ticks(u16 timer_type, u16 par)
{
	u16 retval = 0; /* to silence the compiler */

	switch (timer_type) {
	case AD_CURRENT_WHILE_TIMER:	/* for rx machine usage */
		if (par)
			retval = (AD_SHORT_TIMEOUT_TIME*ad_ticks_per_sec);
		else
			retval = (AD_LONG_TIMEOUT_TIME*ad_ticks_per_sec);
		break;
	case AD_ACTOR_CHURN_TIMER:	/* for local churn machine */
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		break;
	case AD_PERIODIC_TIMER:		/* for periodic machine */
		retval = (par*ad_ticks_per_sec); /* long timeout */
		break;
	case AD_PARTNER_CHURN_TIMER:	/* for remote churn machine */
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		break;
	case AD_WAIT_WHILE_TIMER:	/* for selection machine */
		retval = (AD_AGGREGATE_WAIT_TIME*ad_ticks_per_sec);
		break;
	}

	return retval;
}