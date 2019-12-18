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
typedef  int u32 ;
struct ina3221_data {int /*<<< orphan*/ * fields; int /*<<< orphan*/  reg_config; } ;

/* Variables and functions */
 size_t F_CVRF ; 
 int ina3221_reg_to_interval_us (int /*<<< orphan*/ ) ; 
 int regmap_field_read_poll_timeout (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static inline int ina3221_wait_for_data(struct ina3221_data *ina)
{
	u32 wait, cvrf;

	wait = ina3221_reg_to_interval_us(ina->reg_config);

	/* Polling the CVRF bit to make sure read data is ready */
	return regmap_field_read_poll_timeout(ina->fields[F_CVRF],
					      cvrf, cvrf, wait, wait * 2);
}