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
struct v4l2_jpegcompression {int /*<<< orphan*/  jpeg_markers; int /*<<< orphan*/  COM_len; int /*<<< orphan*/  APP_len; int /*<<< orphan*/  APPn; int /*<<< orphan*/  quality; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_jpegcompression(const void *arg, bool write_only)
{
	const struct v4l2_jpegcompression *p = arg;

	pr_cont("quality=%d, APPn=%d, APP_len=%d, COM_len=%d, jpeg_markers=0x%x\n",
		p->quality, p->APPn, p->APP_len,
		p->COM_len, p->jpeg_markers);
}