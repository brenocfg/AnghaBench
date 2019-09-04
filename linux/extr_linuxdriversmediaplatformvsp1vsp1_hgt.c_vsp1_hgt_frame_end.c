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
typedef  int /*<<< orphan*/  u32 ;
struct vsp1_histogram_buffer {int /*<<< orphan*/ * addr; } ;
struct vsp1_hgt {int /*<<< orphan*/  histo; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HGT_DATA_SIZE ; 
 int /*<<< orphan*/  VI6_HGT_HISTO (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VI6_HGT_MAXMIN ; 
 int /*<<< orphan*/  VI6_HGT_SUM ; 
 struct vsp1_hgt* to_hgt (int /*<<< orphan*/ *) ; 
 void* vsp1_hgt_read (struct vsp1_hgt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_histogram_buffer_complete (int /*<<< orphan*/ *,struct vsp1_histogram_buffer*,int /*<<< orphan*/ ) ; 
 struct vsp1_histogram_buffer* vsp1_histogram_buffer_get (int /*<<< orphan*/ *) ; 

void vsp1_hgt_frame_end(struct vsp1_entity *entity)
{
	struct vsp1_hgt *hgt = to_hgt(&entity->subdev);
	struct vsp1_histogram_buffer *buf;
	unsigned int m;
	unsigned int n;
	u32 *data;

	buf = vsp1_histogram_buffer_get(&hgt->histo);
	if (!buf)
		return;

	data = buf->addr;

	*data++ = vsp1_hgt_read(hgt, VI6_HGT_MAXMIN);
	*data++ = vsp1_hgt_read(hgt, VI6_HGT_SUM);

	for (m = 0; m < 6; ++m)
		for (n = 0; n < 32; ++n)
			*data++ = vsp1_hgt_read(hgt, VI6_HGT_HISTO(m, n));

	vsp1_histogram_buffer_complete(&hgt->histo, buf, HGT_DATA_SIZE);
}