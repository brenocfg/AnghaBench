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
struct ad2s1210_state {int fexcit; int fclkin; TYPE_1__* sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char AD2S1210_MAX_FCW ; 
 unsigned char AD2S1210_MIN_FCW ; 
 unsigned char AD2S1210_REG_EXCIT_FREQ ; 
 int ERANGE ; 
 int ad2s1210_config_write (struct ad2s1210_state*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline
int ad2s1210_update_frequency_control_word(struct ad2s1210_state *st)
{
	int ret;
	unsigned char fcw;

	fcw = (unsigned char)(st->fexcit * (1 << 15) / st->fclkin);
	if (fcw < AD2S1210_MIN_FCW || fcw > AD2S1210_MAX_FCW) {
		dev_err(&st->sdev->dev, "ad2s1210: FCW out of range\n");
		return -ERANGE;
	}

	ret = ad2s1210_config_write(st, AD2S1210_REG_EXCIT_FREQ);
	if (ret < 0)
		return ret;

	return ad2s1210_config_write(st, fcw);
}