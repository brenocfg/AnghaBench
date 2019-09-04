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
struct mag3110_data {int dummy; } ;

/* Variables and functions */
 int mag3110_get_int_plus_micros_index (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mag3110_samp_freq ; 

__attribute__((used)) static int mag3110_get_samp_freq_index(struct mag3110_data *data,
	int val, int val2)
{
	return mag3110_get_int_plus_micros_index(mag3110_samp_freq, 8, val,
		val2);
}