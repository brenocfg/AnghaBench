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
struct si1133_data {scalar_t__ rsp_seq; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI1133_CMD_RESET_CTR ; 
 int /*<<< orphan*/  SI1133_REG_COMMAND ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1133_cmd_reset_counter(struct si1133_data *data)
{
	int err = regmap_write(data->regmap, SI1133_REG_COMMAND,
			       SI1133_CMD_RESET_CTR);
	if (err)
		return err;

	data->rsp_seq = 0;

	return 0;
}