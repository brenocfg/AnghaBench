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
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  code; } ;
struct csis_state {TYPE_1__* csis_fmt; int /*<<< orphan*/  sd; struct v4l2_mbus_framefmt format; } ;
struct TYPE_2__ {int fmt_reg; } ;

/* Variables and functions */
 int S5PCSIS_CFG_FMT_MASK ; 
 int /*<<< orphan*/  S5PCSIS_CONFIG ; 
 int /*<<< orphan*/  S5PCSIS_RESOL ; 
 int /*<<< orphan*/  debug ; 
 int s5pcsis_read (struct csis_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_write (struct csis_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void __s5pcsis_set_format(struct csis_state *state)
{
	struct v4l2_mbus_framefmt *mf = &state->format;
	u32 val;

	v4l2_dbg(1, debug, &state->sd, "fmt: %#x, %d x %d\n",
		 mf->code, mf->width, mf->height);

	/* Color format */
	val = s5pcsis_read(state, S5PCSIS_CONFIG);
	val = (val & ~S5PCSIS_CFG_FMT_MASK) | state->csis_fmt->fmt_reg;
	s5pcsis_write(state, S5PCSIS_CONFIG, val);

	/* Pixel resolution */
	val = (mf->width << 16) | mf->height;
	s5pcsis_write(state, S5PCSIS_RESOL, val);
}