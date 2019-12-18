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
struct s6e63m0 {int dummy; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCS_PGAMMACTL ; 
 struct s6e63m0* bl_get_data (struct backlight_device*) ; 
 int s6e63m0_clear_error (struct s6e63m0*) ; 
 int /*<<< orphan*/  s6e63m0_dcs_write (struct s6e63m0*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e63m0_dcs_write_seq_static (struct s6e63m0*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * s6e63m0_gamma_22 ; 

__attribute__((used)) static int s6e63m0_set_brightness(struct backlight_device *bd)
{
	struct s6e63m0 *ctx = bl_get_data(bd);

	int brightness = bd->props.brightness;

	/* disable and set new gamma */
	s6e63m0_dcs_write(ctx, s6e63m0_gamma_22[brightness],
			  ARRAY_SIZE(s6e63m0_gamma_22[brightness]));

	/* update gamma table. */
	s6e63m0_dcs_write_seq_static(ctx, MCS_PGAMMACTL, 0x01);

	return s6e63m0_clear_error(ctx);
}