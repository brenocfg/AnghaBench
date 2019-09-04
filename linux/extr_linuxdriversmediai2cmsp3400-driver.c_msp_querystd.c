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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct msp_state {int /*<<< orphan*/  detected_std; int /*<<< orphan*/  std; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_standard_std_name (int /*<<< orphan*/ ) ; 
 struct msp_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int msp_querystd(struct v4l2_subdev *sd, v4l2_std_id *id)
{
	struct msp_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	*id &= state->detected_std;

	dev_dbg_lvl(&client->dev, 2, msp_debug,
		"detected standard: %s(0x%08Lx)\n",
		msp_standard_std_name(state->std), state->detected_std);

	return 0;
}