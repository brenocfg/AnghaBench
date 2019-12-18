#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;
struct dp_altmode {TYPE_1__ data; int /*<<< orphan*/  alt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CONF_GET_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEC_MODAL_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int /*<<< orphan*/ ) ; 
 int typec_altmode_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int dp_altmode_notify(struct dp_altmode *dp)
{
	u8 state = get_count_order(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));

	return typec_altmode_notify(dp->alt, TYPEC_MODAL_STATE(state),
				   &dp->data);
}