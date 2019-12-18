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
struct v4l2_subdev {int dummy; } ;
struct adv7842_state {int /*<<< orphan*/  i2c_cp; } ;

/* Variables and functions */
 int adv_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static inline int cp_read(struct v4l2_subdev *sd, u8 reg)
{
	struct adv7842_state *state = to_state(sd);

	return adv_smbus_read_byte_data(state->i2c_cp, reg);
}