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
typedef  int u16 ;
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_SPEC_EFFECTS ; 
#define  V4L2_COLORFX_BW 133 
#define  V4L2_COLORFX_NEGATIVE 132 
#define  V4L2_COLORFX_NONE 131 
#define  V4L2_COLORFX_SEPIA 130 
#define  V4L2_COLORFX_SKETCH 129 
#define  V4L2_COLORFX_SKY_BLUE 128 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void s5k5baf_hw_set_colorfx(struct s5k5baf *state, int val)
{
	static const u16 colorfx[] = {
		[V4L2_COLORFX_NONE] = 0,
		[V4L2_COLORFX_BW] = 1,
		[V4L2_COLORFX_NEGATIVE] = 2,
		[V4L2_COLORFX_SEPIA] = 3,
		[V4L2_COLORFX_SKY_BLUE] = 4,
		[V4L2_COLORFX_SKETCH] = 5,
	};

	s5k5baf_write(state, REG_G_SPEC_EFFECTS, colorfx[val]);
}