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
struct coh901318_params {int dummy; } ;
struct coh901318_chan {size_t id; } ;
struct TYPE_2__ {struct coh901318_params const param; } ;

/* Variables and functions */
 TYPE_1__* chan_config ; 

__attribute__((used)) static inline const struct coh901318_params *
cohc_chan_param(struct coh901318_chan *cohc)
{
	return &chan_config[cohc->id].param;
}