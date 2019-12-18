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
typedef  int u16 ;
struct adt7475_data {int config5; } ;

/* Variables and functions */
 int CONFIG5_TWOSCOMP ; 

__attribute__((used)) static inline int reg2temp(struct adt7475_data *data, u16 reg)
{
	if (data->config5 & CONFIG5_TWOSCOMP) {
		if (reg >= 512)
			return (reg - 1024) * 250;
		else
			return reg * 250;
	} else
		return (reg - 256) * 250;
}