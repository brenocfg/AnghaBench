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
struct input_dev {int dummy; } ;
struct ili210x {int max_touches; scalar_t__ model; int /*<<< orphan*/  prop; struct input_dev* input; } ;

/* Variables and functions */
 scalar_t__ MODEL_ILI210X ; 
 scalar_t__ MODEL_ILI251X ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int ili210x_touchdata_to_coords (struct ili210x*,int*,int,unsigned int*,unsigned int*) ; 
 int ili251x_touchdata_to_coords (struct ili210x*,int*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  touchscreen_report_pos (struct input_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static bool ili210x_report_events(struct ili210x *priv, u8 *touchdata)
{
	struct input_dev *input = priv->input;
	int i;
	bool contact = false, touch = false;
	unsigned int x = 0, y = 0;

	for (i = 0; i < priv->max_touches; i++) {
		if (priv->model == MODEL_ILI210X) {
			touch = ili210x_touchdata_to_coords(priv, touchdata,
							    i, &x, &y);
		} else if (priv->model == MODEL_ILI251X) {
			touch = ili251x_touchdata_to_coords(priv, touchdata,
							    i, &x, &y);
			if (touch)
				contact = true;
		}

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, touch);
		if (!touch)
			continue;
		touchscreen_report_pos(input, &priv->prop, x, y,
				       true);
	}

	input_mt_report_pointer_emulation(input, false);
	input_sync(input);

	if (priv->model == MODEL_ILI210X)
		contact = touchdata[0] & 0xf3;

	return contact;
}