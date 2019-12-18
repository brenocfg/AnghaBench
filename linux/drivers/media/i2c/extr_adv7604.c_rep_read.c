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
struct adv76xx_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV76XX_PAGE_REP ; 
 int adv76xx_read_check (struct adv76xx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static inline int rep_read(struct v4l2_subdev *sd, u8 reg)
{
	struct adv76xx_state *state = to_state(sd);

	return adv76xx_read_check(state, ADV76XX_PAGE_REP, reg);
}