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
struct v4l2_subdev {int dummy; } ;
struct adv76xx_reg_seq {scalar_t__ reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 scalar_t__ ADV76XX_REG_SEQ_TERM ; 
 int /*<<< orphan*/  adv76xx_write_reg (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adv76xx_write_reg_seq(struct v4l2_subdev *sd,
				  const struct adv76xx_reg_seq *reg_seq)
{
	unsigned int i;

	for (i = 0; reg_seq[i].reg != ADV76XX_REG_SEQ_TERM; i++)
		adv76xx_write_reg(sd, reg_seq[i].reg, reg_seq[i].val);
}