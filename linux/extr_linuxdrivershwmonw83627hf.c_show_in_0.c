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
typedef  int u8 ;
struct w83627hf_data {int vrm_ovt; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IN_FROM_REG (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 scalar_t__ w83627thf ; 
 scalar_t__ w83637hf ; 
 scalar_t__ w83687thf ; 

__attribute__((used)) static ssize_t show_in_0(struct w83627hf_data *data, char *buf, u8 reg)
{
	long in0;

	if ((data->vrm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))

		/* use VRM9 calculation */
		in0 = (long)((reg * 488 + 70000 + 50) / 100);
	else
		/* use VRM8 (standard) calculation */
		in0 = (long)IN_FROM_REG(reg);

	return sprintf(buf,"%ld\n", in0);
}