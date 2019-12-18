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
typedef  int /*<<< orphan*/  u8 ;
struct si1145_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1145_CMD_PARAM_SET ; 
 int si1145_param_update (struct si1145_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1145_param_set(struct si1145_data *data, u8 param, u8 value)
{
	return si1145_param_update(data, SI1145_CMD_PARAM_SET, param, value);
}