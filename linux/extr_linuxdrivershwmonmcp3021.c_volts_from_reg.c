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
struct mcp3021_data {int vdd; int output_res; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 

__attribute__((used)) static inline u16 volts_from_reg(struct mcp3021_data *data, u16 val)
{
	return DIV_ROUND_CLOSEST(data->vdd * val, 1 << data->output_res);
}