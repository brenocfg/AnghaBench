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
struct input_mt_pos {int x; int y; } ;
struct alps_fields {struct input_mt_pos* mt; struct input_mt_pos st; int /*<<< orphan*/  y_map; int /*<<< orphan*/  x_map; } ;
struct alps_data {int x_max; int x_bits; int y_max; int y_bits; scalar_t__ proto_version; int second_touch; } ;
struct alps_bitmap_point {int num_bits; int start_bit; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ ALPS_PROTO_V3 ; 
 scalar_t__ ALPS_PROTO_V4 ; 
 scalar_t__ ALPS_PROTO_V5 ; 
 int /*<<< orphan*/  alps_get_bitmap_points (int /*<<< orphan*/ ,struct alps_bitmap_point*,struct alps_bitmap_point*,int*) ; 
 void* max (int,int) ; 

__attribute__((used)) static int alps_process_bitmap(struct alps_data *priv,
			       struct alps_fields *fields)
{
	int i, fingers_x = 0, fingers_y = 0, fingers, closest;
	struct alps_bitmap_point x_low = {0,}, x_high = {0,};
	struct alps_bitmap_point y_low = {0,}, y_high = {0,};
	struct input_mt_pos corner[4];

	if (!fields->x_map || !fields->y_map)
		return 0;

	alps_get_bitmap_points(fields->x_map, &x_low, &x_high, &fingers_x);
	alps_get_bitmap_points(fields->y_map, &y_low, &y_high, &fingers_y);

	/*
	 * Fingers can overlap, so we use the maximum count of fingers
	 * on either axis as the finger count.
	 */
	fingers = max(fingers_x, fingers_y);

	/*
	 * If an axis reports only a single contact, we have overlapping or
	 * adjacent fingers. Divide the single contact between the two points.
	 */
	if (fingers_x == 1) {
		i = (x_low.num_bits - 1) / 2;
		x_low.num_bits = x_low.num_bits - i;
		x_high.start_bit = x_low.start_bit + i;
		x_high.num_bits = max(i, 1);
	}
	if (fingers_y == 1) {
		i = (y_low.num_bits - 1) / 2;
		y_low.num_bits = y_low.num_bits - i;
		y_high.start_bit = y_low.start_bit + i;
		y_high.num_bits = max(i, 1);
	}

	/* top-left corner */
	corner[0].x =
		(priv->x_max * (2 * x_low.start_bit + x_low.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[0].y =
		(priv->y_max * (2 * y_low.start_bit + y_low.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* top-right corner */
	corner[1].x =
		(priv->x_max * (2 * x_high.start_bit + x_high.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[1].y =
		(priv->y_max * (2 * y_low.start_bit + y_low.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* bottom-right corner */
	corner[2].x =
		(priv->x_max * (2 * x_high.start_bit + x_high.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[2].y =
		(priv->y_max * (2 * y_high.start_bit + y_high.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* bottom-left corner */
	corner[3].x =
		(priv->x_max * (2 * x_low.start_bit + x_low.num_bits - 1)) /
		(2 * (priv->x_bits - 1));
	corner[3].y =
		(priv->y_max * (2 * y_high.start_bit + y_high.num_bits - 1)) /
		(2 * (priv->y_bits - 1));

	/* x-bitmap order is reversed on v5 touchpads  */
	if (priv->proto_version == ALPS_PROTO_V5) {
		for (i = 0; i < 4; i++)
			corner[i].x = priv->x_max - corner[i].x;
	}

	/* y-bitmap order is reversed on v3 and v4 touchpads  */
	if (priv->proto_version == ALPS_PROTO_V3 ||
	    priv->proto_version == ALPS_PROTO_V4) {
		for (i = 0; i < 4; i++)
			corner[i].y = priv->y_max - corner[i].y;
	}

	/*
	 * We only select a corner for the second touch once per 2 finger
	 * touch sequence to avoid the chosen corner (and thus the coordinates)
	 * jumping around when the first touch is in the middle.
	 */
	if (priv->second_touch == -1) {
		/* Find corner closest to our st coordinates */
		closest = 0x7fffffff;
		for (i = 0; i < 4; i++) {
			int dx = fields->st.x - corner[i].x;
			int dy = fields->st.y - corner[i].y;
			int distance = dx * dx + dy * dy;

			if (distance < closest) {
				priv->second_touch = i;
				closest = distance;
			}
		}
		/* And select the opposite corner to use for the 2nd touch */
		priv->second_touch = (priv->second_touch + 2) % 4;
	}

	fields->mt[0] = fields->st;
	fields->mt[1] = corner[priv->second_touch];

	return fingers;
}