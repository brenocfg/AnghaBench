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
struct cx2341x_mpeg_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx2341x_calc_audio_properties (struct cx2341x_mpeg_params*) ; 
 struct cx2341x_mpeg_params default_params ; 

void cx2341x_fill_defaults(struct cx2341x_mpeg_params *p)
{
	*p = default_params;
	cx2341x_calc_audio_properties(p);
}