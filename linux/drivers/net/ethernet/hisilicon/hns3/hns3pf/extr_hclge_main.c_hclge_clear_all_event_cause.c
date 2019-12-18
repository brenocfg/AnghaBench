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
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_CORERESET_INT_B ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_EVENT_MBX ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_EVENT_RST ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_GLOBALRESET_INT_B ; 
 int /*<<< orphan*/  HCLGE_VECTOR0_IMPRESET_INT_B ; 
 int /*<<< orphan*/  hclge_clear_event_cause (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_clear_all_event_cause(struct hclge_dev *hdev)
{
	hclge_clear_event_cause(hdev, HCLGE_VECTOR0_EVENT_RST,
				BIT(HCLGE_VECTOR0_GLOBALRESET_INT_B) |
				BIT(HCLGE_VECTOR0_CORERESET_INT_B) |
				BIT(HCLGE_VECTOR0_IMPRESET_INT_B));
	hclge_clear_event_cause(hdev, HCLGE_VECTOR0_EVENT_MBX, 0);
}