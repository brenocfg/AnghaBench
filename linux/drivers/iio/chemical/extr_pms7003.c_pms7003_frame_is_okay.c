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
typedef  scalar_t__ u16 ;
struct pms7003_frame {int length; scalar_t__ data; } ;

/* Variables and functions */
 int PMS7003_CHECKSUM_LENGTH ; 
 scalar_t__ get_unaligned_be16 (scalar_t__) ; 
 scalar_t__ pms7003_calc_checksum (struct pms7003_frame*) ; 

__attribute__((used)) static bool pms7003_frame_is_okay(struct pms7003_frame *frame)
{
	int offset = frame->length - PMS7003_CHECKSUM_LENGTH;
	u16 checksum = get_unaligned_be16(frame->data + offset);

	return checksum == pms7003_calc_checksum(frame);
}