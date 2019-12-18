#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct ivtv {TYPE_2__* card; } ;
struct TYPE_3__ {int mask; int radio; } ;
struct TYPE_4__ {TYPE_1__ gpio_audio_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_GPIO_OUT ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 struct ivtv* sd_to_ivtv (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subdev_s_radio(struct v4l2_subdev *sd)
{
	struct ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_input.mask;
	data = itv->card->gpio_audio_input.radio;
	if (mask)
		write_reg((read_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	return 0;
}