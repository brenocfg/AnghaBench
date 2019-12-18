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
struct cyttsp_xydata {int touch12_id; int touch34_id; } ;

/* Variables and functions */

__attribute__((used)) static void cyttsp_extract_track_ids(struct cyttsp_xydata *xy_data, int *ids)
{
	ids[0] = xy_data->touch12_id >> 4;
	ids[1] = xy_data->touch12_id & 0xF;
	ids[2] = xy_data->touch34_id >> 4;
	ids[3] = xy_data->touch34_id & 0xF;
}