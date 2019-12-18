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
struct lg4573 {int dummy; } ;

/* Variables and functions */
 int lg4573_display_on (struct lg4573*) ; 

__attribute__((used)) static int lg4573_power_on(struct lg4573 *ctx)
{
	return lg4573_display_on(ctx);
}