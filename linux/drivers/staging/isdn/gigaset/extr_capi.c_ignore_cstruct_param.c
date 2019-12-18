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
struct cardstate {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__* _cstruct ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static inline void ignore_cstruct_param(struct cardstate *cs, _cstruct param,
					char *msgname, char *paramname)
{
	if (param && *param)
		dev_warn(cs->dev, "%s: ignoring unsupported parameter: %s\n",
			 msgname, paramname);
}