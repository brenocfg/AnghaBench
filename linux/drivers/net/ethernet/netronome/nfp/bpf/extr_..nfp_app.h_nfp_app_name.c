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
struct nfp_app {TYPE_1__* type; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *nfp_app_name(struct nfp_app *app)
{
	if (!app)
		return "";
	return app->type->name;
}