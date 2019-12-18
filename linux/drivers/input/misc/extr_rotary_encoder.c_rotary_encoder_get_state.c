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
struct rotary_encoder {scalar_t__ encoding; TYPE_1__* gpios; } ;
struct TYPE_2__ {int ndescs; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 scalar_t__ ROTENC_GRAY ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rotary_encoder_get_state(struct rotary_encoder *encoder)
{
	int i;
	unsigned int ret = 0;

	for (i = 0; i < encoder->gpios->ndescs; ++i) {
		int val = gpiod_get_value_cansleep(encoder->gpios->desc[i]);

		/* convert from gray encoding to normal */
		if (encoder->encoding == ROTENC_GRAY && ret & 1)
			val = !val;

		ret = ret << 1 | val;
	}

	return ret & 3;
}