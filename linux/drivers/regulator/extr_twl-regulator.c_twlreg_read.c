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
struct twlreg_info {unsigned int base; } ;

/* Variables and functions */
 int twl_i2c_read_u8 (unsigned int,int*,unsigned int) ; 

__attribute__((used)) static inline int
twlreg_read(struct twlreg_info *info, unsigned slave_subgp, unsigned offset)
{
	u8 value;
	int status;

	status = twl_i2c_read_u8(slave_subgp,
			&value, info->base + offset);
	return (status < 0) ? status : value;
}