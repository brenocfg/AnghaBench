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
struct fxas21002c_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SEL ; 
 int fxas21002c_hpf_value_from_sel (struct fxas21002c_data*,int) ; 
 int fxas21002c_write (struct fxas21002c_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_hpf_set(struct fxas21002c_data *data, int sel)
{
	int sel_bits;

	sel_bits = fxas21002c_hpf_value_from_sel(data, sel);
	if (sel_bits < 0)
		return sel_bits;

	return fxas21002c_write(data, F_SEL, sel_bits);
}