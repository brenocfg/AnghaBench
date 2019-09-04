#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ rangelow; scalar_t__ rangehigh; } ;

/* Variables and functions */
 TYPE_1__* si476x_bands ; 

__attribute__((used)) static inline bool si476x_radio_freq_is_inside_of_the_band(u32 freq, int band)
{
	return freq >= si476x_bands[band].rangelow &&
		freq <= si476x_bands[band].rangehigh;
}