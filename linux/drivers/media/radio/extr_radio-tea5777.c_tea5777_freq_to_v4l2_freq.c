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
struct radio_tea5777 {int band; } ;

/* Variables and functions */
#define  BAND_AM 129 
#define  BAND_FM 128 
 int TEA5777_AM_FREQ_STEP ; 
 int TEA5777_AM_IF ; 
 int TEA5777_FM_FREQ_STEP ; 
 int TEA5777_FM_IF ; 

__attribute__((used)) static u32 tea5777_freq_to_v4l2_freq(struct radio_tea5777 *tea, u32 freq)
{
	switch (tea->band) {
	case BAND_FM:
		return (freq * TEA5777_FM_FREQ_STEP + TEA5777_FM_IF) * 16;
	case BAND_AM:
		return (freq * TEA5777_AM_FREQ_STEP + TEA5777_AM_IF) * 16;
	}
	return 0; /* Never reached */
}