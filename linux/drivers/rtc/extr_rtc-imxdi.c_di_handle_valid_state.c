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
typedef  int u32 ;
struct imxdi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCALR ; 
 int /*<<< orphan*/  DCAMR ; 
 int DCAMR_UNSET ; 
 int /*<<< orphan*/  DSR ; 
 int DSR_CAF ; 
 int /*<<< orphan*/  di_write_busy_wait (struct imxdi_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int di_handle_valid_state(struct imxdi_dev *imxdi, u32 dsr)
{
	/* initialize alarm */
	di_write_busy_wait(imxdi, DCAMR_UNSET, DCAMR);
	di_write_busy_wait(imxdi, 0, DCALR);

	/* clear alarm flag */
	if (dsr & DSR_CAF)
		di_write_busy_wait(imxdi, DSR_CAF, DSR);

	return 0;
}