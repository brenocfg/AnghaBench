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
typedef  int u32 ;
struct v4l2_mbus_framefmt {int width; int height; } ;
struct csi_state {TYPE_1__* csis_fmt; struct v4l2_mbus_framefmt format_mbus; } ;
struct TYPE_2__ {int fmt_reg; } ;

/* Variables and functions */
 int MIPI_CSIS_ISPCFG_FMT_MASK ; 
 int /*<<< orphan*/  MIPI_CSIS_ISPCONFIG_CH0 ; 
 int /*<<< orphan*/  MIPI_CSIS_ISPRESOL_CH0 ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __mipi_csis_set_format(struct csi_state *state)
{
	struct v4l2_mbus_framefmt *mf = &state->format_mbus;
	u32 val;

	/* Color format */
	val = mipi_csis_read(state, MIPI_CSIS_ISPCONFIG_CH0);
	val = (val & ~MIPI_CSIS_ISPCFG_FMT_MASK) | state->csis_fmt->fmt_reg;
	mipi_csis_write(state, MIPI_CSIS_ISPCONFIG_CH0, val);

	/* Pixel resolution */
	val = mf->width | (mf->height << 16);
	mipi_csis_write(state, MIPI_CSIS_ISPRESOL_CH0, val);
}