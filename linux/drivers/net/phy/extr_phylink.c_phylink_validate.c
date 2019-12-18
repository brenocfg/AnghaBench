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
struct phylink_link_state {int dummy; } ;
struct phylink {int /*<<< orphan*/  config; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* validate ) (int /*<<< orphan*/ ,unsigned long*,struct phylink_link_state*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ phylink_is_empty_linkmode (unsigned long*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long*,struct phylink_link_state*) ; 

__attribute__((used)) static int phylink_validate(struct phylink *pl, unsigned long *supported,
			    struct phylink_link_state *state)
{
	pl->ops->validate(pl->config, supported, state);

	return phylink_is_empty_linkmode(supported) ? -EINVAL : 0;
}