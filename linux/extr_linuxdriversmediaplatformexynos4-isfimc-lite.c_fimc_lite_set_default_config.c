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
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; void* height; void* width; } ;
struct flite_frame {TYPE_1__ rect; void* f_height; void* f_width; int /*<<< orphan*/ * fmt; } ;
struct fimc_lite {struct flite_frame out_frame; struct flite_frame inp_frame; } ;

/* Variables and functions */
 void* FLITE_DEFAULT_HEIGHT ; 
 void* FLITE_DEFAULT_WIDTH ; 
 int /*<<< orphan*/ * fimc_lite_formats ; 

__attribute__((used)) static void fimc_lite_set_default_config(struct fimc_lite *fimc)
{
	struct flite_frame *sink = &fimc->inp_frame;
	struct flite_frame *source = &fimc->out_frame;

	sink->fmt = &fimc_lite_formats[0];
	sink->f_width = FLITE_DEFAULT_WIDTH;
	sink->f_height = FLITE_DEFAULT_HEIGHT;

	sink->rect.width = FLITE_DEFAULT_WIDTH;
	sink->rect.height = FLITE_DEFAULT_HEIGHT;
	sink->rect.left = 0;
	sink->rect.top = 0;

	*source = *sink;
}