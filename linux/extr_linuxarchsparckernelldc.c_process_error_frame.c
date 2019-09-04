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
struct ldc_packet {int dummy; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int LDC_ABORT (struct ldc_channel*) ; 

__attribute__((used)) static int process_error_frame(struct ldc_channel *lp,
			       struct ldc_packet *p)
{
	return LDC_ABORT(lp);
}