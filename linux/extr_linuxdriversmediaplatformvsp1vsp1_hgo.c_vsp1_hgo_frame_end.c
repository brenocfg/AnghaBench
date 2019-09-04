#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct vsp1_histogram_buffer {void** addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsp1; } ;
struct TYPE_5__ {TYPE_1__ entity; } ;
struct vsp1_hgo {int num_bins; TYPE_2__ histo; scalar_t__ max_rgb; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_HGO_B_HISTO (unsigned int) ; 
 int /*<<< orphan*/  VI6_HGO_B_MAXMIN ; 
 int /*<<< orphan*/  VI6_HGO_B_SUM ; 
 int /*<<< orphan*/  VI6_HGO_EXT_HIST_ADDR ; 
 int /*<<< orphan*/  VI6_HGO_EXT_HIST_DATA ; 
 int /*<<< orphan*/  VI6_HGO_G_HISTO (unsigned int) ; 
 int /*<<< orphan*/  VI6_HGO_G_MAXMIN ; 
 int /*<<< orphan*/  VI6_HGO_G_SUM ; 
 int /*<<< orphan*/  VI6_HGO_R_HISTO (unsigned int) ; 
 int /*<<< orphan*/  VI6_HGO_R_MAXMIN ; 
 int /*<<< orphan*/  VI6_HGO_R_SUM ; 
 struct vsp1_hgo* to_hgo (int /*<<< orphan*/ *) ; 
 void* vsp1_hgo_read (struct vsp1_hgo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_histogram_buffer_complete (TYPE_2__*,struct vsp1_histogram_buffer*,size_t) ; 
 struct vsp1_histogram_buffer* vsp1_histogram_buffer_get (TYPE_2__*) ; 
 int /*<<< orphan*/  vsp1_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void vsp1_hgo_frame_end(struct vsp1_entity *entity)
{
	struct vsp1_hgo *hgo = to_hgo(&entity->subdev);
	struct vsp1_histogram_buffer *buf;
	unsigned int i;
	size_t size;
	u32 *data;

	buf = vsp1_histogram_buffer_get(&hgo->histo);
	if (!buf)
		return;

	data = buf->addr;

	if (hgo->num_bins == 256) {
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_SUM);

		for (i = 0; i < 256; ++i) {
			vsp1_write(hgo->histo.entity.vsp1,
				   VI6_HGO_EXT_HIST_ADDR, i);
			*data++ = vsp1_hgo_read(hgo, VI6_HGO_EXT_HIST_DATA);
		}

		size = (2 + 256) * sizeof(u32);
	} else if (hgo->max_rgb) {
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_SUM);

		for (i = 0; i < 64; ++i)
			*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_HISTO(i));

		size = (2 + 64) * sizeof(u32);
	} else {
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_R_MAXMIN);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_MAXMIN);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_B_MAXMIN);

		*data++ = vsp1_hgo_read(hgo, VI6_HGO_R_SUM);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_G_SUM);
		*data++ = vsp1_hgo_read(hgo, VI6_HGO_B_SUM);

		for (i = 0; i < 64; ++i) {
			data[i] = vsp1_hgo_read(hgo, VI6_HGO_R_HISTO(i));
			data[i+64] = vsp1_hgo_read(hgo, VI6_HGO_G_HISTO(i));
			data[i+128] = vsp1_hgo_read(hgo, VI6_HGO_B_HISTO(i));
		}

		size = (6 + 64 * 3) * sizeof(u32);
	}

	vsp1_histogram_buffer_complete(&hgo->histo, buf, size);
}