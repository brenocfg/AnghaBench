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
struct chp_id {size_t id; int /*<<< orphan*/  cssid; } ;
struct channel_path {int dummy; } ;
struct TYPE_2__ {struct channel_path** chps; } ;

/* Variables and functions */
 TYPE_1__* css_by_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct channel_path *chpid_to_chp(struct chp_id chpid)
{
	return css_by_id(chpid.cssid)->chps[chpid.id];
}