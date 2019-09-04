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
struct mma8452_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mma8452_get_int_plus_micros_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mma8452_samp_freq ; 

__attribute__((used)) static int mma8452_get_samp_freq_index(struct mma8452_data *data,
				       int val, int val2)
{
	return mma8452_get_int_plus_micros_index(mma8452_samp_freq,
						 ARRAY_SIZE(mma8452_samp_freq),
						 val, val2);
}