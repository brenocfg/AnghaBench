#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int report_count; int report_size; } ;
struct hid_parser {int /*<<< orphan*/  scan_flags; TYPE_1__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_SCAN_FLAG_MT_WIN_8 ; 

__attribute__((used)) static void hid_scan_feature_usage(struct hid_parser *parser, u32 usage)
{
	if (usage == 0xff0000c5 && parser->global.report_count == 256 &&
	    parser->global.report_size == 8)
		parser->scan_flags |= HID_SCAN_FLAG_MT_WIN_8;
}