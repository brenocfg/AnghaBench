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
struct sil164_encoder_params {int input_skew; int duallink_skew; scalar_t__ pll_filter; scalar_t__ input_dual; scalar_t__ input_width; scalar_t__ input_edge; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIL164_CONTROL0 ; 
 int SIL164_CONTROL0_DUAL_EDGE ; 
 int SIL164_CONTROL0_EDGE_RISING ; 
 int SIL164_CONTROL0_HSYNC_ON ; 
 int SIL164_CONTROL0_INPUT_24BIT ; 
 int SIL164_CONTROL0_VSYNC_ON ; 
 int /*<<< orphan*/  SIL164_CONTROL1 ; 
 int SIL164_CONTROL1_DESKEW_ENABLE ; 
 int SIL164_CONTROL1_DESKEW_INCR_SHIFT ; 
 int /*<<< orphan*/  SIL164_CONTROL2 ; 
 int SIL164_CONTROL2_FILTER_ENABLE ; 
 int SIL164_CONTROL2_FILTER_SETTING_SHIFT ; 
 int SIL164_CONTROL2_SYNC_CONT ; 
 int /*<<< orphan*/  SIL164_DETECT ; 
 int SIL164_DETECT_INTR_STAT ; 
 int SIL164_DETECT_OUT_MODE_RECEIVER ; 
 int /*<<< orphan*/  SIL164_DUALLINK ; 
 int SIL164_DUALLINK_ENABLE ; 
 int SIL164_DUALLINK_SKEW_SHIFT ; 
 int /*<<< orphan*/  SIL164_PLLZONE ; 
 int /*<<< orphan*/  sil164_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sil164_init_state(struct i2c_client *client,
		  struct sil164_encoder_params *config,
		  bool duallink)
{
	sil164_write(client, SIL164_CONTROL0,
		     SIL164_CONTROL0_HSYNC_ON |
		     SIL164_CONTROL0_VSYNC_ON |
		     (config->input_edge ? SIL164_CONTROL0_EDGE_RISING : 0) |
		     (config->input_width ? SIL164_CONTROL0_INPUT_24BIT : 0) |
		     (config->input_dual ? SIL164_CONTROL0_DUAL_EDGE : 0));

	sil164_write(client, SIL164_DETECT,
		     SIL164_DETECT_INTR_STAT |
		     SIL164_DETECT_OUT_MODE_RECEIVER);

	sil164_write(client, SIL164_CONTROL1,
		     (config->input_skew ? SIL164_CONTROL1_DESKEW_ENABLE : 0) |
		     (((config->input_skew + 4) & 0x7)
		      << SIL164_CONTROL1_DESKEW_INCR_SHIFT));

	sil164_write(client, SIL164_CONTROL2,
		     SIL164_CONTROL2_SYNC_CONT |
		     (config->pll_filter ? 0 : SIL164_CONTROL2_FILTER_ENABLE) |
		     (4 << SIL164_CONTROL2_FILTER_SETTING_SHIFT));

	sil164_write(client, SIL164_PLLZONE, 0);

	if (duallink)
		sil164_write(client, SIL164_DUALLINK,
			     SIL164_DUALLINK_ENABLE |
			     (((config->duallink_skew + 4) & 0x7)
			      << SIL164_DUALLINK_SKEW_SHIFT));
	else
		sil164_write(client, SIL164_DUALLINK, 0);
}