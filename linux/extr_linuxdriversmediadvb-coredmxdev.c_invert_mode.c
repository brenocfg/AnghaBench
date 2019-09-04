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
struct dmx_filter {int* mode; } ;

/* Variables and functions */
 int DMX_FILTER_SIZE ; 

__attribute__((used)) static inline void invert_mode(struct dmx_filter *filter)
{
	int i;

	for (i = 0; i < DMX_FILTER_SIZE; i++)
		filter->mode[i] ^= 0xff;
}