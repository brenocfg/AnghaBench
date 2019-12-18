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
struct sis_video_info {int /*<<< orphan*/  SiS_Pr; } ;

/* Variables and functions */
 unsigned short SiS_ReadDDC1Bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sisfb_test_DDC1(struct sis_video_info *ivideo)
{
    unsigned short old;
    int count = 48;

    old = SiS_ReadDDC1Bit(&ivideo->SiS_Pr);
    do {
	if(old != SiS_ReadDDC1Bit(&ivideo->SiS_Pr)) break;
    } while(count--);
    return (count != -1);
}