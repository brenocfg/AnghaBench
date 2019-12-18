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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_ADEC_CONTROL ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_PROC_SOFT_RESET ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 

void cx18_halt_firmware(struct cx18 *cx)
{
	CX18_DEBUG_INFO("Preparing for firmware halt.\n");
	cx18_write_reg_expect(cx, 0x000F000F, CX18_PROC_SOFT_RESET,
				  0x0000000F, 0x000F000F);
	cx18_write_reg_expect(cx, 0x00020002, CX18_ADEC_CONTROL,
				  0x00000002, 0x00020002);
}