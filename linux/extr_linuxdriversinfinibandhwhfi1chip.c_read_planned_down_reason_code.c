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
typedef  int u8 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int DOWN_REMOTE_REASON_MASK ; 
 int DOWN_REMOTE_REASON_SHIFT ; 
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int /*<<< orphan*/  LINK_QUALITY_INFO ; 
 int /*<<< orphan*/  read_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void read_planned_down_reason_code(struct hfi1_devdata *dd, u8 *pdrrc)
{
	u32 frame;

	read_8051_config(dd, LINK_QUALITY_INFO, GENERAL_CONFIG, &frame);
	*pdrrc = (frame >> DOWN_REMOTE_REASON_SHIFT) & DOWN_REMOTE_REASON_MASK;
}