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
struct mei_cl {TYPE_1__* me_cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  client_id; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 mei_cl_me_id(const struct mei_cl *cl)
{
	return cl->me_cl ? cl->me_cl->client_id : 0;
}