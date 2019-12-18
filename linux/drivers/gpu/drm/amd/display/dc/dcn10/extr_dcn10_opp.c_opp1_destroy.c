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
struct output_pixel_processor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_DCN10_OPP (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void opp1_destroy(struct output_pixel_processor **opp)
{
	kfree(TO_DCN10_OPP(*opp));
	*opp = NULL;
}