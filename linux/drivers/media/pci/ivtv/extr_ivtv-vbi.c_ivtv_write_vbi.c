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
struct vbi_cc {int /*<<< orphan*/  even; int /*<<< orphan*/  odd; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct ivtv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ivtv_write_vbi_cc_lines (struct ivtv*,struct vbi_cc*) ; 
 int /*<<< orphan*/  ivtv_write_vbi_line (struct ivtv*,struct v4l2_sliced_vbi_data const*,struct vbi_cc*,int*) ; 

__attribute__((used)) static void ivtv_write_vbi(struct ivtv *itv,
			   const struct v4l2_sliced_vbi_data *sliced,
			   size_t cnt)
{
	struct vbi_cc cc = { .odd = { 0x80, 0x80 }, .even = { 0x80, 0x80 } };
	int found_cc = 0;
	size_t i;

	for (i = 0; i < cnt; i++)
		ivtv_write_vbi_line(itv, sliced + i, &cc, &found_cc);

	if (found_cc)
		ivtv_write_vbi_cc_lines(itv, &cc);
}