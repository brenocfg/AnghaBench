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
struct TYPE_2__ {int /*<<< orphan*/  pix_clk_khz; } ;
struct dc_stream_state {TYPE_1__ timing; int /*<<< orphan*/  phy_pix_clk; int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 scalar_t__ dc_is_hdmi_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_norm_pix_clk (TYPE_1__*) ; 

__attribute__((used)) static void calculate_phy_pix_clks(struct dc_stream_state *stream)
{
	/* update actual pixel clock on all streams */
	if (dc_is_hdmi_signal(stream->signal))
		stream->phy_pix_clk = get_norm_pix_clk(
			&stream->timing);
	else
		stream->phy_pix_clk =
			stream->timing.pix_clk_khz;
}