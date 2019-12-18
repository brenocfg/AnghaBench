#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stimx274 {TYPE_1__* mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  init_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx274_start_1 ; 
 int imx274_write_table (struct stimx274*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx274_mode_regs(struct stimx274 *priv)
{
	int err = 0;

	err = imx274_write_table(priv, imx274_start_1);
	if (err)
		return err;

	err = imx274_write_table(priv, priv->mode->init_regs);

	return err;
}