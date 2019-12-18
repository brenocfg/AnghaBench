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
struct g2d_frame {int c_width; int c_height; } ;
struct g2d_dev {int dummy; } ;

/* Variables and functions */
 int DEFAULT_SCALE_MODE ; 
 int /*<<< orphan*/  SRC_SCALE_CTRL_REG ; 
 int /*<<< orphan*/  SRC_XSCALE_REG ; 
 int /*<<< orphan*/  SRC_YSCALE_REG ; 
 int /*<<< orphan*/  w (int,int /*<<< orphan*/ ) ; 

void g2d_set_v41_stretch(struct g2d_dev *d, struct g2d_frame *src,
					struct g2d_frame *dst)
{
	w(DEFAULT_SCALE_MODE, SRC_SCALE_CTRL_REG);

	/* inversed scaling factor: src is numerator */
	w((src->c_width << 16) / dst->c_width, SRC_XSCALE_REG);
	w((src->c_height << 16) / dst->c_height, SRC_YSCALE_REG);
}