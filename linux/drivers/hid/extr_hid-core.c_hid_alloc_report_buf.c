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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct hid_report {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

u8 *hid_alloc_report_buf(struct hid_report *report, gfp_t flags)
{
	/*
	 * 7 extra bytes are necessary to achieve proper functionality
	 * of implement() working on 8 byte chunks
	 */

	u32 len = hid_report_len(report) + 7;

	return kmalloc(len, flags);
}