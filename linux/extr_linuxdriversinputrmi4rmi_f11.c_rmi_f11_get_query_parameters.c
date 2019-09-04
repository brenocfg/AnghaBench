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
typedef  scalar_t__ u16 ;
struct rmi_device {int dummy; } ;
struct f11_data {int has_acm; scalar_t__ has_query28; scalar_t__ has_query27; scalar_t__ has_query12; scalar_t__ has_query11; scalar_t__ has_query9; } ;
struct f11_2d_sensor_queries {int nr_fingers; int has_rel; int has_abs; int has_gestures; int has_sensitivity_adjust; int configurable; int nr_x_electrodes; int nr_y_electrodes; int max_electrodes; int abs_data_size; int has_anchored_finger; int has_adj_hyst; int has_dribble; int has_bending_correction; int has_large_object_suppression; int has_jitter_filter; int f11_2d_query6; int has_single_tap; int has_tap_n_hold; int has_double_tap; int has_early_tap; int has_flick; int has_press; int has_pinch; int has_chiral; int has_palm_det; int has_rotate; int has_touch_shapes; int has_scroll_zones; int has_individual_scroll_zones; int has_mf_scroll; int has_mf_edge_motion; int has_mf_scroll_inertia; int query7_nonzero; int query8_nonzero; int has_pen; int has_proximity; int has_palm_det_sensitivity; int has_suppress_on_palm_detect; int has_two_pen_thresholds; int has_contact_geometry; int has_pen_hover_discrimination; int has_pen_filters; int nr_touch_shapes; int has_z_tuning; int has_algorithm_selection; int has_w_tuning; int has_pitch_info; int has_finger_size; int has_segmentation_aggressiveness; int has_XY_clip; int has_drumming_filter; int has_gapless_finger; int has_gapless_finger_tuning; int has_8bit_w; int has_adjustable_mapping; int has_info2; int has_physical_props; int has_finger_limit; int has_linear_coeff_2; int jitter_window_size; int jitter_filter_type; int light_control; int is_clear; int clickpad_props; int mouse_buttons; int has_advanced_gestures; int x_sensor_size_mm; int y_sensor_size_mm; } ;

/* Variables and functions */
 int BIT (int) ; 
 int RMI_F11_ABS_DATA_SIZE_MASK ; 
 int RMI_F11_CLICKPAD_PROPS_MASK ; 
 int RMI_F11_CLICKPAD_PROPS_SHIFT ; 
 int RMI_F11_CONFIGURABLE ; 
 int RMI_F11_HAS_8BIT_W ; 
 int RMI_F11_HAS_ABS ; 
 int RMI_F11_HAS_ADJUSTABLE_MAPPING ; 
 int RMI_F11_HAS_ADJ_HYST ; 
 int RMI_F11_HAS_ADVANCED_GESTURES ; 
 int RMI_F11_HAS_ALGORITHM_SELECTION ; 
 int RMI_F11_HAS_ANCHORED_FINGER ; 
 int RMI_F11_HAS_BENDING_CORRECTION ; 
 int RMI_F11_HAS_CHIRAL ; 
 int RMI_F11_HAS_CONTACT_GEOMETRY ; 
 int RMI_F11_HAS_DOUBLE_TAP ; 
 int RMI_F11_HAS_DRIBBLE ; 
 int RMI_F11_HAS_DRUMMING_FILTER ; 
 int RMI_F11_HAS_EARLY_TAP ; 
 int RMI_F11_HAS_FINGER_LIMIT ; 
 int RMI_F11_HAS_FINGER_SIZE ; 
 int RMI_F11_HAS_FLICK ; 
 int RMI_F11_HAS_GAPLESS_FINGER ; 
 int RMI_F11_HAS_GAPLESS_FINGER_TUNING ; 
 int RMI_F11_HAS_GESTURES ; 
 int RMI_F11_HAS_INDIVIDUAL_SCROLL_ZONES ; 
 int RMI_F11_HAS_INFO2 ; 
 int RMI_F11_HAS_JITTER_FILTER ; 
 int RMI_F11_HAS_LARGE_OBJECT_SUPPRESSION ; 
 int RMI_F11_HAS_LINEAR_COEFF ; 
 int RMI_F11_HAS_MF_EDGE_MOTION ; 
 int RMI_F11_HAS_MF_SCROLL ; 
 int RMI_F11_HAS_MF_SCROLL_INERTIA ; 
 int RMI_F11_HAS_PALM_DET ; 
 int RMI_F11_HAS_PALM_DET_SENSITIVITY ; 
 int RMI_F11_HAS_PEN ; 
 int RMI_F11_HAS_PEN_FILTERS ; 
 int RMI_F11_HAS_PEN_HOVER_DISCRIMINATION ; 
 int RMI_F11_HAS_PHYSICAL_PROPS ; 
 int RMI_F11_HAS_PINCH ; 
 int RMI_F11_HAS_PITCH_INFO ; 
 int RMI_F11_HAS_PRESS ; 
 int RMI_F11_HAS_PROXIMITY ; 
 int RMI_F11_HAS_REL ; 
 int RMI_F11_HAS_ROTATE ; 
 int RMI_F11_HAS_SCROLL_ZONES ; 
 int RMI_F11_HAS_SEGMENTATION_AGGRESSIVENESS ; 
 int RMI_F11_HAS_SENSITIVITY_ADJ ; 
 int RMI_F11_HAS_SINGLE_TAP ; 
 int RMI_F11_HAS_SUPPRESS_ON_PALM_DETECT ; 
 int RMI_F11_HAS_TAP_AND_HOLD ; 
 int RMI_F11_HAS_TOUCH_SHAPES ; 
 int RMI_F11_HAS_TWO_PEN_THRESHOLDS ; 
 int RMI_F11_HAS_W_TUNING ; 
 int RMI_F11_HAS_XY_CLIP ; 
 int RMI_F11_HAS_Z_TUNING ; 
 int RMI_F11_IS_CLEAR ; 
 int RMI_F11_JITTER_FILTER_MASK ; 
 int RMI_F11_JITTER_FILTER_SHIFT ; 
 int RMI_F11_JITTER_WINDOW_MASK ; 
 int RMI_F11_LIGHT_CONTROL_MASK ; 
 int RMI_F11_MOUSE_BUTTONS_MASK ; 
 int RMI_F11_MOUSE_BUTTONS_SHIFT ; 
 int RMI_F11_NR_ELECTRODES_MASK ; 
 int RMI_F11_NR_FINGERS_MASK ; 
 int RMI_F11_NR_TOUCH_SHAPES_MASK ; 
 int RMI_F11_QUERY_GESTURE_SIZE ; 
 int RMI_F11_QUERY_SIZE ; 
 int rmi_read (struct rmi_device*,scalar_t__,int*) ; 
 int rmi_read_block (struct rmi_device*,scalar_t__,int*,int) ; 

__attribute__((used)) static int rmi_f11_get_query_parameters(struct rmi_device *rmi_dev,
			struct f11_data *f11,
			struct f11_2d_sensor_queries *sensor_query,
			u16 query_base_addr)
{
	int query_size;
	int rc;
	u8 query_buf[RMI_F11_QUERY_SIZE];
	bool has_query36 = false;

	rc = rmi_read_block(rmi_dev, query_base_addr, query_buf,
				RMI_F11_QUERY_SIZE);
	if (rc < 0)
		return rc;

	sensor_query->nr_fingers = query_buf[0] & RMI_F11_NR_FINGERS_MASK;
	sensor_query->has_rel = !!(query_buf[0] & RMI_F11_HAS_REL);
	sensor_query->has_abs = !!(query_buf[0] & RMI_F11_HAS_ABS);
	sensor_query->has_gestures = !!(query_buf[0] & RMI_F11_HAS_GESTURES);
	sensor_query->has_sensitivity_adjust =
		!!(query_buf[0] & RMI_F11_HAS_SENSITIVITY_ADJ);
	sensor_query->configurable = !!(query_buf[0] & RMI_F11_CONFIGURABLE);

	sensor_query->nr_x_electrodes =
				query_buf[1] & RMI_F11_NR_ELECTRODES_MASK;
	sensor_query->nr_y_electrodes =
				query_buf[2] & RMI_F11_NR_ELECTRODES_MASK;
	sensor_query->max_electrodes =
				query_buf[3] & RMI_F11_NR_ELECTRODES_MASK;

	query_size = RMI_F11_QUERY_SIZE;

	if (sensor_query->has_abs) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->abs_data_size =
			query_buf[0] & RMI_F11_ABS_DATA_SIZE_MASK;
		sensor_query->has_anchored_finger =
			!!(query_buf[0] & RMI_F11_HAS_ANCHORED_FINGER);
		sensor_query->has_adj_hyst =
			!!(query_buf[0] & RMI_F11_HAS_ADJ_HYST);
		sensor_query->has_dribble =
			!!(query_buf[0] & RMI_F11_HAS_DRIBBLE);
		sensor_query->has_bending_correction =
			!!(query_buf[0] & RMI_F11_HAS_BENDING_CORRECTION);
		sensor_query->has_large_object_suppression =
			!!(query_buf[0] & RMI_F11_HAS_LARGE_OBJECT_SUPPRESSION);
		sensor_query->has_jitter_filter =
			!!(query_buf[0] & RMI_F11_HAS_JITTER_FILTER);
		query_size++;
	}

	if (sensor_query->has_rel) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size,
					&sensor_query->f11_2d_query6);
		if (rc < 0)
			return rc;
		query_size++;
	}

	if (sensor_query->has_gestures) {
		rc = rmi_read_block(rmi_dev, query_base_addr + query_size,
					query_buf, RMI_F11_QUERY_GESTURE_SIZE);
		if (rc < 0)
			return rc;

		sensor_query->has_single_tap =
			!!(query_buf[0] & RMI_F11_HAS_SINGLE_TAP);
		sensor_query->has_tap_n_hold =
			!!(query_buf[0] & RMI_F11_HAS_TAP_AND_HOLD);
		sensor_query->has_double_tap =
			!!(query_buf[0] & RMI_F11_HAS_DOUBLE_TAP);
		sensor_query->has_early_tap =
			!!(query_buf[0] & RMI_F11_HAS_EARLY_TAP);
		sensor_query->has_flick =
			!!(query_buf[0] & RMI_F11_HAS_FLICK);
		sensor_query->has_press =
			!!(query_buf[0] & RMI_F11_HAS_PRESS);
		sensor_query->has_pinch =
			!!(query_buf[0] & RMI_F11_HAS_PINCH);
		sensor_query->has_chiral =
			!!(query_buf[0] & RMI_F11_HAS_CHIRAL);

		/* query 8 */
		sensor_query->has_palm_det =
			!!(query_buf[1] & RMI_F11_HAS_PALM_DET);
		sensor_query->has_rotate =
			!!(query_buf[1] & RMI_F11_HAS_ROTATE);
		sensor_query->has_touch_shapes =
			!!(query_buf[1] & RMI_F11_HAS_TOUCH_SHAPES);
		sensor_query->has_scroll_zones =
			!!(query_buf[1] & RMI_F11_HAS_SCROLL_ZONES);
		sensor_query->has_individual_scroll_zones =
			!!(query_buf[1] & RMI_F11_HAS_INDIVIDUAL_SCROLL_ZONES);
		sensor_query->has_mf_scroll =
			!!(query_buf[1] & RMI_F11_HAS_MF_SCROLL);
		sensor_query->has_mf_edge_motion =
			!!(query_buf[1] & RMI_F11_HAS_MF_EDGE_MOTION);
		sensor_query->has_mf_scroll_inertia =
			!!(query_buf[1] & RMI_F11_HAS_MF_SCROLL_INERTIA);

		sensor_query->query7_nonzero = !!(query_buf[0]);
		sensor_query->query8_nonzero = !!(query_buf[1]);

		query_size += 2;
	}

	if (f11->has_query9) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->has_pen =
			!!(query_buf[0] & RMI_F11_HAS_PEN);
		sensor_query->has_proximity =
			!!(query_buf[0] & RMI_F11_HAS_PROXIMITY);
		sensor_query->has_palm_det_sensitivity =
			!!(query_buf[0] & RMI_F11_HAS_PALM_DET_SENSITIVITY);
		sensor_query->has_suppress_on_palm_detect =
			!!(query_buf[0] & RMI_F11_HAS_SUPPRESS_ON_PALM_DETECT);
		sensor_query->has_two_pen_thresholds =
			!!(query_buf[0] & RMI_F11_HAS_TWO_PEN_THRESHOLDS);
		sensor_query->has_contact_geometry =
			!!(query_buf[0] & RMI_F11_HAS_CONTACT_GEOMETRY);
		sensor_query->has_pen_hover_discrimination =
			!!(query_buf[0] & RMI_F11_HAS_PEN_HOVER_DISCRIMINATION);
		sensor_query->has_pen_filters =
			!!(query_buf[0] & RMI_F11_HAS_PEN_FILTERS);

		query_size++;
	}

	if (sensor_query->has_touch_shapes) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->nr_touch_shapes = query_buf[0] &
				RMI_F11_NR_TOUCH_SHAPES_MASK;

		query_size++;
	}

	if (f11->has_query11) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->has_z_tuning =
			!!(query_buf[0] & RMI_F11_HAS_Z_TUNING);
		sensor_query->has_algorithm_selection =
			!!(query_buf[0] & RMI_F11_HAS_ALGORITHM_SELECTION);
		sensor_query->has_w_tuning =
			!!(query_buf[0] & RMI_F11_HAS_W_TUNING);
		sensor_query->has_pitch_info =
			!!(query_buf[0] & RMI_F11_HAS_PITCH_INFO);
		sensor_query->has_finger_size =
			!!(query_buf[0] & RMI_F11_HAS_FINGER_SIZE);
		sensor_query->has_segmentation_aggressiveness =
			!!(query_buf[0] &
				RMI_F11_HAS_SEGMENTATION_AGGRESSIVENESS);
		sensor_query->has_XY_clip =
			!!(query_buf[0] & RMI_F11_HAS_XY_CLIP);
		sensor_query->has_drumming_filter =
			!!(query_buf[0] & RMI_F11_HAS_DRUMMING_FILTER);

		query_size++;
	}

	if (f11->has_query12) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->has_gapless_finger =
			!!(query_buf[0] & RMI_F11_HAS_GAPLESS_FINGER);
		sensor_query->has_gapless_finger_tuning =
			!!(query_buf[0] & RMI_F11_HAS_GAPLESS_FINGER_TUNING);
		sensor_query->has_8bit_w =
			!!(query_buf[0] & RMI_F11_HAS_8BIT_W);
		sensor_query->has_adjustable_mapping =
			!!(query_buf[0] & RMI_F11_HAS_ADJUSTABLE_MAPPING);
		sensor_query->has_info2 =
			!!(query_buf[0] & RMI_F11_HAS_INFO2);
		sensor_query->has_physical_props =
			!!(query_buf[0] & RMI_F11_HAS_PHYSICAL_PROPS);
		sensor_query->has_finger_limit =
			!!(query_buf[0] & RMI_F11_HAS_FINGER_LIMIT);
		sensor_query->has_linear_coeff_2 =
			!!(query_buf[0] & RMI_F11_HAS_LINEAR_COEFF);

		query_size++;
	}

	if (sensor_query->has_jitter_filter) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->jitter_window_size = query_buf[0] &
			RMI_F11_JITTER_WINDOW_MASK;
		sensor_query->jitter_filter_type = (query_buf[0] &
			RMI_F11_JITTER_FILTER_MASK) >>
			RMI_F11_JITTER_FILTER_SHIFT;

		query_size++;
	}

	if (sensor_query->has_info2) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size, query_buf);
		if (rc < 0)
			return rc;

		sensor_query->light_control =
			query_buf[0] & RMI_F11_LIGHT_CONTROL_MASK;
		sensor_query->is_clear =
			!!(query_buf[0] & RMI_F11_IS_CLEAR);
		sensor_query->clickpad_props =
			(query_buf[0] & RMI_F11_CLICKPAD_PROPS_MASK) >>
			RMI_F11_CLICKPAD_PROPS_SHIFT;
		sensor_query->mouse_buttons =
			(query_buf[0] & RMI_F11_MOUSE_BUTTONS_MASK) >>
			RMI_F11_MOUSE_BUTTONS_SHIFT;
		sensor_query->has_advanced_gestures =
			!!(query_buf[0] & RMI_F11_HAS_ADVANCED_GESTURES);

		query_size++;
	}

	if (sensor_query->has_physical_props) {
		rc = rmi_read_block(rmi_dev, query_base_addr
			+ query_size, query_buf, 4);
		if (rc < 0)
			return rc;

		sensor_query->x_sensor_size_mm =
			(query_buf[0] | (query_buf[1] << 8)) / 10;
		sensor_query->y_sensor_size_mm =
			(query_buf[2] | (query_buf[3] << 8)) / 10;

		/*
		 * query 15 - 18 contain the size of the sensor
		 * and query 19 - 26 contain bezel dimensions
		 */
		query_size += 12;
	}

	if (f11->has_query27)
		++query_size;

	if (f11->has_query28) {
		rc = rmi_read(rmi_dev, query_base_addr + query_size,
				query_buf);
		if (rc < 0)
			return rc;

		has_query36 = !!(query_buf[0] & BIT(6));
	}

	if (has_query36) {
		query_size += 2;
		rc = rmi_read(rmi_dev, query_base_addr + query_size,
				query_buf);
		if (rc < 0)
			return rc;

		if (!!(query_buf[0] & BIT(5)))
			f11->has_acm = true;
	}

	return query_size;
}