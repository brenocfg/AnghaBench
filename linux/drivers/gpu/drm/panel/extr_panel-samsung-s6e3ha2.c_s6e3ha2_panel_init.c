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
struct s6e3ha2 {int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_dsi_dcs_exit_sleep_mode (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  s6e3ha2_call_write_func (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e3ha2_freq_calibration (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_single_dsi_set (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_off_f0 (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_off_fc (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_on_f0 (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_on_fc (struct s6e3ha2*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int s6e3ha2_panel_init(struct s6e3ha2 *ctx)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int ret;

	s6e3ha2_call_write_func(ret, mipi_dsi_dcs_exit_sleep_mode(dsi));
	usleep_range(5000, 6000);

	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_on_f0(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_single_dsi_set(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_on_fc(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_freq_calibration(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_off_fc(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_off_f0(ctx));

	return 0;
}