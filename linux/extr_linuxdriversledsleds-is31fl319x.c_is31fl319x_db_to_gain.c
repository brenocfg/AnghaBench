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

/* Variables and functions */
 int IS31FL319X_AUDIO_GAIN_DB_STEP ; 

__attribute__((used)) static inline int is31fl319x_db_to_gain(u32 dezibel)
{ /* round down to nearest supported value (range check done by caller) */
	return dezibel / IS31FL319X_AUDIO_GAIN_DB_STEP;
}