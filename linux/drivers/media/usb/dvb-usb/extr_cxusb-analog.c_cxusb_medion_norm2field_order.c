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
typedef  int v4l2_std_id ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_BT ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 

__attribute__((used)) static u32 cxusb_medion_norm2field_order(v4l2_std_id norm)
{
	bool is625 = norm & V4L2_STD_625_50;
	bool is525 = norm & V4L2_STD_525_60;

	if (!is625 && !is525)
		return V4L2_FIELD_NONE;

	if (is625 && is525)
		return V4L2_FIELD_NONE;

	if (is625)
		return V4L2_FIELD_SEQ_TB;
	else /* is525 */
		return V4L2_FIELD_SEQ_BT;
}