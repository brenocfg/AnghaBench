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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_app {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eswitch_mode_get ) (struct nfp_app*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  stub1 (struct nfp_app*) ; 

__attribute__((used)) static inline int nfp_app_eswitch_mode_get(struct nfp_app *app, u16 *mode)
{
	if (!app->type->eswitch_mode_get)
		return -EOPNOTSUPP;

	*mode = app->type->eswitch_mode_get(app);

	return 0;
}