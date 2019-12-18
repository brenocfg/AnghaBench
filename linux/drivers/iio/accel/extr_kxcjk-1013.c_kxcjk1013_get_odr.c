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
struct kxcjk1013_data {scalar_t__ chipset; int /*<<< orphan*/  odr_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ KXTF9 ; 
 int kxcjk1013_convert_odr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  kxtf9_samp_freq_table ; 
 int /*<<< orphan*/  samp_freq_table ; 

__attribute__((used)) static int kxcjk1013_get_odr(struct kxcjk1013_data *data, int *val, int *val2)
{
	if (data->chipset == KXTF9)
		return kxcjk1013_convert_odr_value(kxtf9_samp_freq_table,
						   ARRAY_SIZE(kxtf9_samp_freq_table),
						   data->odr_bits, val, val2);
	else
		return kxcjk1013_convert_odr_value(samp_freq_table,
						   ARRAY_SIZE(samp_freq_table),
						   data->odr_bits, val, val2);
}