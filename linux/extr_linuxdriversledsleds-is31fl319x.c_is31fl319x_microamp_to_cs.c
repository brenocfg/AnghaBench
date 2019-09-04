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
typedef  int u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int IS31FL319X_CONFIG2_CS_MASK ; 
 int IS31FL319X_CONFIG2_CS_SHIFT ; 
 int IS31FL319X_CONFIG2_CS_STEP_REF ; 
 int IS31FL319X_CURRENT_STEP ; 

__attribute__((used)) static inline int is31fl319x_microamp_to_cs(struct device *dev, u32 microamp)
{ /* round down to nearest supported value (range check done by caller) */
	u32 step = microamp / IS31FL319X_CURRENT_STEP;

	return ((IS31FL319X_CONFIG2_CS_STEP_REF - step) &
		IS31FL319X_CONFIG2_CS_MASK) <<
		IS31FL319X_CONFIG2_CS_SHIFT; /* CS encoding */
}