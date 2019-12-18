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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_app {TYPE_1__* type; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* (* dev_get ) (struct nfp_app*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 struct net_device* stub1 (struct nfp_app*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline
struct net_device *nfp_app_dev_get(struct nfp_app *app, u32 id,
				   bool *redir_egress)
{
	if (unlikely(!app || !app->type->dev_get))
		return NULL;

	return app->type->dev_get(app, id, redir_egress);
}