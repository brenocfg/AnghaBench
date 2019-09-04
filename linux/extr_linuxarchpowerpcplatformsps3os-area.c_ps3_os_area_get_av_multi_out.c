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
typedef  enum ps3_param_av_multi_out { ____Placeholder_ps3_param_av_multi_out } ps3_param_av_multi_out ;
struct TYPE_2__ {int av_multi_out; } ;

/* Variables and functions */
 TYPE_1__ saved_params ; 

enum ps3_param_av_multi_out ps3_os_area_get_av_multi_out(void)
{
    return saved_params.av_multi_out;
}