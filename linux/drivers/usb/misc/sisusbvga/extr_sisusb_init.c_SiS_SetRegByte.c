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
struct SiS_Private {int /*<<< orphan*/  sisusb; } ;

/* Variables and functions */
 int /*<<< orphan*/  sisusb_setreg (int /*<<< orphan*/ ,unsigned long,unsigned short) ; 

__attribute__((used)) static void
SiS_SetRegByte(struct SiS_Private *SiS_Pr, unsigned long port,
	       unsigned short data)
{
	sisusb_setreg(SiS_Pr->sisusb, port, data);
}